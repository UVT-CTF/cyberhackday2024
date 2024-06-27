#!/bin/sh

gcc ./stage.c -o ./maze -lm
timeout --kill-after=1s 10m ./maze
