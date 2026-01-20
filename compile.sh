#!/bin/sh
# Usage: ./compile.sh [build|upload] [PORT]
# Default: upload to /dev/ttyACM0

FQBN="arduino:avr:uno"
PORT="${2:-/dev/ttyACM0}"
MODE="${1:-upload}"

if [ "$MODE" = "build" ]; then
	arduino-cli compile --fqbn "$FQBN" radar.ino
else
	arduino-cli compile --fqbn "$FQBN" --upload -p "$PORT" radar.ino
fi

