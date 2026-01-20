# 1. Set the port speed
stty -F /dev/ttyACM0 9600 raw -echo

# 2. Read the output
cat /dev/ttyACM0
