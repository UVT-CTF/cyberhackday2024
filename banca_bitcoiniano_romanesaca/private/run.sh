#!/bin/sh

gcc ./main.c -o ./BBR -lm
timeout --kill-after=1s 10m ./BBR