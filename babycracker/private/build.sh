#!/bin/bash

if ! command -v upx &> /dev/null
then
    echo "UPX could not be found. Installing UPX..."
    sudo apt-get update
    sudo apt-get install -y upx
fi

mkdir -p ../release

gcc main.c -o ../release/babycracker -fno-stack-protector -no-pie -z execstack -Wl,-z,norelro && strip ../release/babycracker

if [ $? -eq 0 ]; then
    echo "Compilation succeeded. Running UPX..."
    upx --best ../release/babycracker
    chmod +x ../release/babycracker
else
    echo "Compilation failed. UPX will not be run."
fi
