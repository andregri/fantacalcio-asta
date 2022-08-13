import psycopg2
import logging
from tabulate import tabulate

# import my modules
import utils
import estimate


def add_player(player, team, cost, **kwargs):
    db_conn = psycopg2.connect(
        user="admin", password="admin",
        host="127.0.0.1", port="5432",
        database="fantacalcio")
    
    with db_conn.cursor() as cursor:
        # TODO: check that player is available

        # find player id from his name
        try:
            player_id, player_name = utils.find_player_by_name(db_conn, player)
        except Exception as e:
            logging.info(e)
            return

        # find fantasy team id from its name
        cursor.execute(f"""
            SELECT id, name FROM team
            WHERE LOWER(name) LIKE '%' || '{team}' || '%';
        """)
        team_rows = cursor.fetchall()
        
        if len(team_rows) == 0:
            logging.info(f"Unable to find a team from '{team}'")
            return
        
        elif len(team_rows) == 1:
            logging.info(f"Found one team from '{team}': {str(team_rows[0])}")

        elif len(team_rows) > 1:
            logging.info(f"Found many teams from '{team}': {','.join(str(row) for row in team_rows)}")
            return

    # create rows in transfer and roster tables if user confirms
    fantasy_team_id, fantasy_team = team_rows[0]

    while True:
        confirm = input(f"Do you want to add '{player_name}' to '{fantasy_team}' for $ {cost} ? (y/n)")
        if confirm == 'y':
            utils.add_player(db_conn, fantasy_team_id, player_id, cost)
            logging.info(f"Insert transfer: {(player_id, player_name)} $ {cost} -> {team_rows[0]}")
            break

        elif confirm == 'n':
            break

    db_conn.close()


def estimate_offer(player, **kwargs):
    db_conn = psycopg2.connect(
        user="admin", password="admin",
        host="127.0.0.1", port="5432",
        database="fantacalcio")

    # find player id by name
    try:
        player_id, player_name = utils.find_player_by_name(db_conn, player)
    except Exception as e:
        logging.info(e)
        return

    with db_conn.cursor() as cursor:
        # read other attributes of that player
        cursor.execute(f"""
            SELECT role, team, value, fantasy_value FROM player
            WHERE id = {player_id}
        """)
        player_role, player_team, player_value, player_fvalue = cursor.fetchone()

        # find all fantasy teams that have to buy players for that role
        cursor.execute(f"""
            SELECT id, name, COALESCE(num_players, 0)
            FROM team
            LEFT JOIN (
                SELECT roster.fantasy_team_id, COUNT(roster.fantasy_team_id) AS num_players
                FROM roster
                INNER JOIN player ON roster.player_id = player.id
                WHERE player.role = '{player_role}'
                GROUP BY roster.fantasy_team_id) AS count
			ON team.id = count.fantasy_team_id;
        """)
        team_rows = cursor.fetchall()

        offers_dict = {}

        for row in team_rows:
            fantasy_team_id, fantasy_team_name, num_player_bought = row
            num_player_to_buy = estimate.NUM_PER_ROLE[player_role] - num_player_bought

            if num_player_to_buy > 0:
                # compute real and estimated max offer
                max_offer = estimate.max_offer(db_conn, fantasy_team_id)
                estimate_max_offer = estimate.max_estimated_offer(db_conn, fantasy_team_id, player_role, budget=80)

                if estimate_max_offer > 0:
                    offers_dict[fantasy_team_name] = dict(
                        to_buy=num_player_to_buy, max=max_offer, est=estimate_max_offer
                    )

        # sort offers by the estimated offer
        sorted_offers_dict = {k: v for k,v in sorted(offers_dict.items(), key=lambda item: item[1]['est'], reverse=True)}
        table_data = [[k, v['to_buy'], v['max'], v['est']] for k,v in sorted_offers_dict.items()]

        # print data in a table
        print(f"{player_name} ({player_team}) $ {player_fvalue}")
        print(tabulate(table_data, headers=['to_buy', 'max $', 'est $']))

    db_conn.close()