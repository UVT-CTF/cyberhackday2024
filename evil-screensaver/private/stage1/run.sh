#!/bin/bash
source "$(dirname "$0")/venv/bin/activate"
./venv/bin/python3.11 "$(dirname "$0")/prettify.py"