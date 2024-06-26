FROM python:3.10-slim-buster

RUN apt update && apt install -y tcpdump curl && apt clean && rm -rf /var/lib/apt/lists/*

WORKDIR /root

COPY private/app.py /root/app.py

COPY private/entrypoint.sh /root/entrypoint.sh
RUN chmod +x /root/entrypoint.sh

ENTRYPOINT ["/root/entrypoint.sh"]
