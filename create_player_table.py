import xlrd

def toStr(s):
    s = s.replace('\'', '')
    return f"'{s}'"

attributes = {
    "id": {"col": 0, "conv": int},
    "role": {"col": 1, "conv": toStr},
    "name": {"col": 3, "conv": toStr},
    "team": {"col": 4, "conv": toStr},
    "value": {"col": 5, "conv": int},
    "fantasy_value": {"col": 11, "conv": int}
}

create_table_sql = """
CREATE TABLE IF NOT EXISTS player (
    id INTEGER NOT NULL PRIMARY KEY,
    role VARCHAR(1) NOT NULL, 
    name TEXT NOT NULL,
    team TEXT NOT NULL,
    value INTEGER NOT NULL,
    fantasy_value INTEGER NOT NULL
);
"""

xlsx_filename = "files/Quotazioni_Fantacalcio_Stagione_2022_23.xlsx"

if __name__ == "__main__":
    workbook = xlrd.open_workbook(xlsx_filename)
    sheet = workbook.sheet_by_index(0)
    
    with open('player_schema.sql', 'w') as f:
        
        f.write(create_table_sql)

        for row in range(2, sheet.nrows):
            attrs = ",".join(attributes.keys())

            values = ",".join(
                (str(params["conv"](sheet.cell_value(row, params["col"])))
                for params in attributes.values())
            )

            f.write(f"INSERT INTO player ({attrs}) VALUES ({values});\n")
