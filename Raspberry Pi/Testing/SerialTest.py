import serial
import time

serialPort = serial.Serial("/dev/ttyS0", 19200)
serialPort.reset_input_buffer()

time.sleep(1)

while True:
    if serialPort.in_waiting:
        msg = serialPort.read_until(';'.encode()).decode()
        print(msg)

    serialPort.write(input("Input: ").encode())

    time.sleep(1)