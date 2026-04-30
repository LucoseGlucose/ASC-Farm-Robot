import serial
import time

serialToInterface = serial.Serial("/dev/ttyS0", 19200, 8, "N", 1, 1)
serialToInterface.reset_input_buffer()

time.sleep(.25)

while True:
    if serialToInterface.in_waiting > 0:
        print(serialToInterface.readall().decode())
    else:
        string: str = input("-")
        serialToInterface.write(string.encode())