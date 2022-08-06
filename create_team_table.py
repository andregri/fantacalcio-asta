if __name__ == "__main__":
    with open("team_schema.sql", "w") as f:
        f.write("""
            CREATE TABLE IF NOT EXISTS team (
                id SERIAL PRIMARY KEY,
                name TEXT NOT NULL,
                coach TEXT NOT NULL
            );\n
            """)
        f.write("INSERT INTO team (name, coach) VALUES ('Real Pollo', 'AndreaG');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('Pompy FC', 'GianG');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('Patetico Mineiro', 'LucaF');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('Paris Saint Germano', 'LucaL');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('Apoel Kan 1893', 'AndreaV');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('Ire Framba United', 'EdoD');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('Godopolisportiva Antonio Ricci', 'AleC');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('MedusaTeam WFC', 'FedeF');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('Reggisenal', 'DanieleP');\n")
        f.write("INSERT INTO team (name, coach) VALUES ('Rolling Stoned', 'LorenzoP');\n")