#!/bin/sh

gcc ./riddle.c -o ./riddle -lm
timeout --kill-after=1s 10m ./riddle
