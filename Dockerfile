# sudo docker build -t fantadb .
# sudo docker run --rm -p 5432:5432 fantadb
FROM python:3.9 as builder

WORKDIR /usr/src/app
COPY . .
RUN pip install -r requirements.txt
RUN python3 db.py

FROM postgres:14

ENV POSTGRES_USER admin
ENV POSTGRES_PASSWORD admin
ENV POSTGRES_DB fantacalcio

EXPOSE 5432

COPY --from=builder /usr/src/app/schema.sql /docker-entrypoint-initdb.d/create_tables.sql