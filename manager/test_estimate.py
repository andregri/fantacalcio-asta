import psycopg2
import datetime
import logging, sys

import estimate


logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)


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


def populate():
    db_conn = psycopg2.connect(user="admin",
                                  password="admin",
                                  host="127.0.0.1",
                                  port="5432",
                                  database="fantacalcio")

    # Add 3 defenders defenders
    add_player(db_conn, 1, 4292, 30)
    add_player(db_conn, 1, 5513, 20)
    add_player(db_conn, 1, 2788, 15)

    db_conn.close()


if __name__ == "__main__":
    db_conn = psycopg2.connect(user="admin",
                                  password="admin",
                                  host="127.0.0.1",
                                  port="5432",
                                  database="fantacalcio")

    # compute max offers
    estimate.max_offer(db_conn, 1)
    estimate.max_estimated_offer(db_conn, fantasy_team_id=1, role="D", budget=80)

    db_conn.close()