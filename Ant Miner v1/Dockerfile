FROM golang:1.21-alpine
WORKDIR /app
COPY ./private .
RUN go build -o server .
EXPOSE 20220
CMD ["./server"]
