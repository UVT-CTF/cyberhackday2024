FROM gcc:12.2.0-bullseye
RUN apt update -y && apt install -y xinetd && apt clean && rm -rf /var/lib/apt/lists/*

RUN useradd -d /home/solver -u 8888 -m solver
USER solver

COPY --chown=solver:solver xinetd /etc/xinetd.d/xinetd
COPY --chown=solver:solver private /home/solver

RUN chmod +x /home/solver/*

CMD ["/usr/sbin/xinetd", "-dontfork"]
