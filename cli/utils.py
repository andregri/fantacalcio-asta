import datetime
import logging
from multiprocessing.sharedctypes import Value


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


def delete_transfer(db_conn, player_id, fantasy_team_id):
    # must delete from transfer and roster tables
    with db_conn.cursor() as cursor:
        cursor.execute(f"""
            DELETE FROM roster WHERE player_id = {player_id}
            AND fantasy_team_id = {fantasy_team_id};
        """)

        cursor.execute(f"""
            DELETE FROM transfer WHERE player_id = {player_id}
            AND dest_fantasy_team_id = {fantasy_team_id};
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
            logging.info(f"Found many players from '{player_name}': {','.join(str(row) for row in player_rows)}")
            chosen_id = int(input("Please type player id: "))
            ids = [row[0] for row in player_rows]
            if chosen_id in ids:
                return player_rows[ids.index(chosen_id)]
            else:
                raise ValueError(f"{chosen_id} is not among {str(ids)}")