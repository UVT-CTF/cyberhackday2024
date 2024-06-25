FROM python:3.10-slim-buster
RUN apt update -y && apt install -y xinetd && apt clean && rm -rf /var/lib/apt/lists/*

RUN useradd -d /home/solver -u 8888 -m solver
USER solver

RUN pip3 install --no-cache-dir lark==1.1.5
RUN pip3 install requests
RUN pip3 install together

COPY --chown=solver:solver xinetd /etc/xinetd.d/xinetd
COPY --chown=solver:solver private /home/solver

RUN chmod +x /home/solver/*

CMD ["/usr/sbin/xinetd", "-dontfork"]