#!/bin/sh

mkdir -p /tmp

echo "Starting tcpdump" > /tmp/debug.log

tcpdump -i any -w /tmp/capture.pcap port 80 or port 443 2>> /tmp/debug.log &
TCPDUMP_PID=$!

echo "tcpdump PID: $TCPDUMP_PID" >> /tmp/debug.log

sleep 5

echo "Running Python script" >> /tmp/debug.log
python /root/app.py
echo "Python script finished" >> /tmp/debug.log

sleep 10

kill $TCPD
