FROM python:3.8-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt clean && rm -rf /var/lib/apt/lists/*

RUN useradd -d /home/jwt -u 8888 -m jwt
USER jwt

COPY --chown=jwt:jwt private/requirements.txt /home/jwt
COPY --chown=jwt:jwt private/app.py /home/jwt
COPY --chown=jwt:jwt private/flag.txt /home/jwt
COPY --chown=jwt:jwt private/priv.pem /home/jwt
COPY --chown=jwt:jwt private/pub.pem /home/jwt

WORKDIR /home/jwt

RUN python3 -m venv venv
RUN /bin/bash -c "source venv/bin/activate && pip install -r requirements.txt"

ENV FLASK_APP=app.py
ENV FLASK_RUN_HOST=0.0.0.0
ENV FLASK_RUN_PORT=65001

EXPOSE 65001

CMD ["/home/jwt/venv/bin/flask", "run"]
