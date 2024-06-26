#!/bin/bash

port=12346


while true; do
    output=$(./spacious.exe)
    echo "$output" | nc -l -p $port -w 1
done

