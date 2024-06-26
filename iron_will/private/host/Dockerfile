FROM python:3.9-slim

RUN apt-get update && \
    apt-get install -y curl build-essential libgcc1 libc6

RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y

ENV PATH="/root/.cargo/bin:${PATH}"
ENV RUST_BACKTRACE=full


WORKDIR /app

COPY . /app

RUN chmod +x /app/iron_will

EXPOSE 12345

CMD ["python", "server.py"]
