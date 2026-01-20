#!/bin/sh
# upload.sh — compile and upload sketch, auto-detecting the serial port
# Usage: ./upload.sh [port]

FQBN="arduino:avr:uno"
SKETCH="radar.ino"

# optional override
if [ -n "$1" ]; then
  PORT="$1"
else
  # try arduino-cli board list first
  PORT=$(arduino-cli board list 2>/dev/null | awk '/\/dev/ {print $1; exit}')
  # fallback to common device names
  if [ -z "$PORT" ]; then
    PORT=$(ls /dev/ttyACM* /dev/ttyUSB* 2>/dev/null | head -n1)
  fi
fi

if [ -z "$PORT" ]; then
  echo "No serial port detected. Plug in your Arduino or run: ./upload.sh /dev/ttyACM0"
  exit 1
fi

echo "Using port: $PORT"

echo "Compiling $SKETCH..."
arduino-cli compile --fqbn "$FQBN" "$SKETCH" || { echo "Compile failed"; exit 2; }

echo "Uploading to $PORT..."
arduino-cli upload -p "$PORT" --fqbn "$FQBN" "$SKETCH" || { echo "Upload failed"; exit 3; }

echo "Upload complete. Open serial at 9600 baud to view output."
