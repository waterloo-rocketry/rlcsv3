#!/bin/bash

# This assumes both arduinos are plugged into your linux laptop, and it connects the two serial ports together while printing all data being sent.

trap killgroup SIGINT

killgroup() {
  kill 0
}

stty 115200 -F /dev/ttyACM* raw
stty 115200 -F /dev/ttyUSB1 raw

cat /dev/ttyACM* > /dev/ttyUSB1 &
cat /dev/ttyUSB1 | tee /dev/ttyACM* &
wait
