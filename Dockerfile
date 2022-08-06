# sudo docker build -t fantadb .
# sudo docker run --rm --name fantadb1 -p 5432:5432 fantadb
# sudo docker exec -it fantadb1 bash
# psql -U admin fantacalcio
# sudo docker stop fantadb1
FROM python:3.9 as builder

WORKDIR /usr/src/app
COPY . .
RUN pip install -r requirements.txt
RUN python3 create_team_table.py
RUN python3 create_player_table.py
RUN python3 create_transfer_table.py
RUN python3 create_roster_table.py

FROM postgres:14

ENV POSTGRES_USER admin
ENV POSTGRES_PASSWORD admin
ENV POSTGRES_DB fantacalcio

EXPOSE 5432

# append many files into create_tables.sql
COPY --from=builder /usr/src/app/team_schema.sql /docker-entrypoint-initdb.d/create_tables_1.sql
COPY --from=builder /usr/src/app/player_schema.sql /docker-entrypoint-initdb.d/create_tables_2.sql
COPY --from=builder /usr/src/app/transfer_schema.sql /docker-entrypoint-initdb.d/create_tables_3.sql
COPY --from=builder /usr/src/app/roster_schema.sql /docker-entrypoint-initdb.d/create_tables_4.sql