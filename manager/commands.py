from sqlite3 import Cursor
import psycopg2
import logging

# import my modules
import utils


def add_player(player, team, cost, **kwargs):
    db_conn = psycopg2.connect(
        user="admin", password="admin",
        host="127.0.0.1", port="5432",
        database="fantacalcio")
    
    with db_conn.cursor() as cursor:
        # find player id from his name
        cursor.execute(f"""
            SELECT id, name FROM player
            WHERE lower(name) LIKE '%' || '{player}' || '%';
        """)
        player_rows = cursor.fetchall()

        if len(player_rows) == 0:
            logging.info(f"Unable to find a player from '{player}'")
            return
        
        elif len(player_rows) == 1:
            logging.info(f"Found one player from '{player}': {str(player_rows[0])}")
        
        elif len(player_rows) > 1:
            logging.info(f"Found many players from '{player}': {','.join(str(row) for row in player_rows)}")
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

    # create rows in transfer and roster tables
    player_id, player_name = player_rows[0]
    fantasy_team_id, fantasy_team = team_rows[0]

    confirm = input(f"Do you want to add '{player_name}' to '{fantasy_team}' for $ {cost} ? (y/n)")
    if confirm == 'y':
        utils.add_player(db_conn, fantasy_team_id, player_id, cost)
        logging.info(f"Insert transfer: {player_rows[0]} $ {cost} -> {team_rows[0]}")

    db_conn.close()


def estimate_offer(player, **kwargs):
    pass