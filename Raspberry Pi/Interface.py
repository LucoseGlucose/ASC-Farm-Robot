import serial
import time

serialToInterface = serial.Serial("/dev/ttyS0", 19200, timeout=1)
serialToInterface.reset_input_buffer()

time.sleep(.25)

while (string := input()) != "quit":
    serialToInterface.write(string.encode())