FROM python:3.10-slim-buster

RUN apt update -y && \
    apt install -y xinetd && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

RUN useradd -d /home/rev1 -u 8888 -m rev1
USER rev1

COPY --chown=rev1:rev1 private/xinetd /etc/xinetd.d/xinetd
COPY --chown=rev1:rev1 private/service.py /home/rev1

RUN chmod +x /home/rev1/*

EXPOSE 9001

CMD ["/usr/sbin/xinetd", "-dontfork"]
