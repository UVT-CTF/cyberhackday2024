#!/bin/bash

# File containing the pixel values
PIXEL_FILE="pixels.txt"

# Destination IP and port
DEST_IP="192.168.0.59"
DEST_PORT="38899"

# Read the file line by line
while IFS= read -r line
do

  # Extract the RGB values from the line
  line=$(echo $line | tr -d '[]')
  IFS=',' read -r -a rgb <<< "$line"
  
  # Assign RGB values
  r=${rgb[0]}
  g=${rgb[1]}
  b=${rgb[2]}

  # Construct the JSON payload
  payload=$(printf '{"id":1,"method":"setPilot","params":{"r":%d,"g":%d,"b":%d,"dimming":55}}' "$r" "$g" "$b")

  # Execute the command
  echo "$payload" | nc -u -w 1 $DEST_IP $DEST_PORT &
  sleep 0.002

done < "$PIXEL_FILE"
