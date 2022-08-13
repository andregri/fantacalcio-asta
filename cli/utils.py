import datetime
import logging


def add_player(db_conn, fantasy_team_id, player_id, cost):
    with db_conn.cursor() as cursor:
        cursor.execute(f"""
            INSERT INTO transfer(created, player_id, dest_fantasy_team_id, cost)
            VALUES ('{datetime.datetime.now(datetime.timezone.utc)}', {player_id}, {fantasy_team_id}, {cost})
            RETURNING id;
        """)
        transfer_id = cursor.fetchone()[0]

        logging.debug(f"Transfer id: {transfer_id}")

        cursor.execute(f"""
            INSERT INTO roster(player_id, fantasy_team_id, transfer_id)
            VALUES ({player_id}, {fantasy_team_id}, {transfer_id});
        """)

        db_conn.commit()

def find_player_by_name(db_conn, player_name):
    with db_conn.cursor() as cursor:
        cursor.execute(f"""
            SELECT id, name FROM player
            WHERE lower(name) LIKE '%' || '{player_name}' || '%';
        """)
        player_rows = cursor.fetchall()

        if len(player_rows) == 0:
            raise ValueError(f"Unable to find a player from '{player_name}'")

        elif len(player_rows) == 1:
            logging.info(f"Found one player from '{player_name}': {str(player_rows[0])}")
            return player_rows[0]

        elif len(player_rows) > 1:
            raise ValueError(f"Found many players from '{player_name}': {','.join(str(row) for row in player_rows)}")