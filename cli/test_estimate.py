import psycopg2
import logging, sys

# import my modules
import estimate
import utils


logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)


def populate():
    db_conn = psycopg2.connect(user="admin",
                                  password="admin",
                                  host="127.0.0.1",
                                  port="5432",
                                  database="fantacalcio")

    # Add 3 defenders defenders
    utils.add_player(db_conn, 1, 4292, 30)
    utils.add_player(db_conn, 2, 5513, 20)
    utils.add_player(db_conn, 3, 2788, 15)

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