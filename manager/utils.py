import datetime
import logging


def add_player(db_conn, fantasy_team_id, player_id, cost):
    with db_conn.cursor() as cursor:
        cursor.execute(f"""
            INSERT INTO transfer(created, player_id, dest_fantasy_team_id, cost)
            VALUES ('{datetime.datetime.now()}', {player_id}, {fantasy_team_id}, {cost})
            RETURNING id;
        """)
        transfer_id = cursor.fetchone()[0]

        logging.debug(f"Transfer id: {transfer_id}")

        cursor.execute(f"""
            INSERT INTO roster(player_id, fantasy_team_id, transfer_id)
            VALUES ({player_id}, {fantasy_team_id}, {transfer_id});
        """)

        db_conn.commit()