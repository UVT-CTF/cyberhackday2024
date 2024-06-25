FROM python:3.10-slim-buster

RUN useradd -d /home/rev0 -u 8888 -m rev0

USER rev0
WORKDIR /home/rev0/

COPY --chown=rev0:rev0 private/server/app.py /home/rev0/app.py

RUN pip install flask

EXPOSE 5000

CMD ["python", "app.py"]
