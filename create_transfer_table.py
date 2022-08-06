if __name__ == "__main__":
    with open("transfer_schema.sql", "w") as f:
        f.write("""
            CREATE TABLE IF NOT EXISTS transfer (
                id SERIAL PRIMARY KEY,
                created TIMESTAMP,
                player_id INTEGER REFERENCES player(id) NOT NULL,
                source_fantasy_team_id INTEGER REFERENCES team(id),
                dest_fantasy_team_id INTEGER REFERENCES team(id) NOT NULL,
                cost INTEGER NOT NULL
            );""")