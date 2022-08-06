import psycopg2
import logging, sys


logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

INITIAL_CREDITS = 500
NUM_PER_ROLE = {
    "P": 3,
    "D": 8,
    "C": 8,
    "A": 6
}
NUM_ROSTER = sum((num for num in NUM_PER_ROLE.values()))

def max_offer(db_conn, fantasy_team_id):
    with db_conn.cursor() as cursor:
        cursor.execute(f"""
            SELECT SUM(transfer.cost), COUNT(transfer.cost)
            FROM roster
            INNER JOIN transfer
            ON roster.transfer_id = transfer.id
            WHERE roster.fantasy_team_id = {fantasy_team_id};
        """)
        roster_cost, num_buyed_players = cursor.fetchall()[0]
        num_missing_players = NUM_ROSTER - num_buyed_players

        logging.debug(f"Total Cost of team {fantasy_team_id} is {roster_cost}")
        logging.debug(f"Number of missing player of team {fantasy_team_id} is {num_missing_players}")

        max_offer = INITIAL_CREDITS - roster_cost - num_missing_players + 1

        logging.debug(f"Max offer of team {fantasy_team_id} is {max_offer}")

        db_conn.commit()

    return max_offer



def max_estimated_offer(db_conn, fantasy_team_id, role, budget):
    with db_conn.cursor() as cursor:
        cursor.execute(f"""
            SELECT SUM(transfer.cost), COUNT(transfer.cost)
            FROM roster
            INNER JOIN transfer ON roster.transfer_id = transfer.id
            WHERE roster.fantasy_team_id = {fantasy_team_id}
            AND roster.player_id IN (
                SELECT id FROM player
                WHERE role = '{role}'
            );
        """)

        player_tot_cost, num_buyed_players = cursor.fetchall()[0]
        num_missing_players = NUM_PER_ROLE[role] - num_buyed_players

        logging.debug(f"Total Cost of team {fantasy_team_id} per {role} role is {player_tot_cost}")
        logging.debug(f"Number of missing player of team {fantasy_team_id} per {role} role is {num_missing_players}")

        max_offer_estimate = budget - player_tot_cost - (8 - num_missing_players + 1)

        logging.debug(f"Estimated max offer of team {fantasy_team_id} is {max_offer_estimate}")

        db_conn.commit()    
    
    return max_offer_estimate