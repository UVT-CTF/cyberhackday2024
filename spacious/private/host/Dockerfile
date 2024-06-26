FROM python:3.9-slim

RUN apt-get update && \
    apt-get install -y curl build-essential libgcc1 libc6 netcat-openbsd


WORKDIR /app

COPY . /app

RUN chmod +x /app/server.sh

EXPOSE 12346

CMD ["./server.sh"]
