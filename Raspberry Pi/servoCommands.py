import serial
import time

s = serial.Serial("/dev/ttyACM0", 115200, timeout=1)
s.reset_input_buffer()

delimiter = ';'

def writeCommand(command: str):
    s.write((command + delimiter).encode())

while (command := input("Enter Command: ")) != "quit":
    writeCommand(command)
    time.sleep(1)