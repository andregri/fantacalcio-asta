import xlrd
import pprint
import datetime


create_table = """
CREATE TABLE IF NOT EXISTS roster (
    player_id INTEGER REFERENCES player(id),
    fantasy_team_id INTEGER REFERENCES team(id),
    transfer_id INTEGER REFERENCES transfer(id)
);
"""



class Rosters:
    def __init__(self, filename) -> None:
        workbook = xlrd.open_workbook(filename)
        self.worksheet = workbook.sheet_by_index(0)

    def print(self, row_offset, col_offset):
        col_offset = col_offset * 5
        row_offset = 6 + row_offset * 4 + row_offset * 25
        for row in range(row_offset, row_offset+25):
            for col in range(col_offset, col_offset+4):
                # Print the cell values with tab space
                print(self.worksheet.cell_value(row, col), end='\t')
            print('')
    
    def list(self, row_offset, col_offset):
        roster = []

        col_offset = col_offset * 5
        row_offset = 6 + row_offset * 4 + row_offset * 25
        for row in range(row_offset, row_offset+25):
            roster.append({
                'Created': datetime.datetime.now(),
                'Role': self.worksheet.cell_value(row, col_offset+0),
                'Name': self.worksheet.cell_value(row, col_offset+1),
                'Team': self.worksheet.cell_value(row, col_offset+2),
                'Cost': self.worksheet.cell_value(row, col_offset+3)
            })
        return roster


if __name__ == "__main__":
    #rosters = Rosters('files/rose.xlsx')
    #with open('schema.sql', 'w') as f:
    #    f.write(create_table)
    #    
    #    roster1 = rosters.list(0,0)
    #    for player in roster1:
    #        created = player['Created']
    #        role = player['Role']
    #        name = player['Name'].replace('\'', '')
    #        team = player['Team']
    #        cost = player['Cost']
    #        f.write(f"INSERT INTO roster (created, role, name, team, cost) VALUES ('{created}', '{role}', '{name}', '{team}', {cost});\n")

    with open("roster_schema.sql", "w") as f:
        f.write(create_table)