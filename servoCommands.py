import serial
import time

s = serial.Serial("/dev/ttyACM0", 115200, timeout=1)

while (command := input("Enter Command: ")) is not "quit":
    
    if (command is "off"):
        s.write("off\0")
    
    if (command is "on"):
        s.write("on\0")
    
    time.sleep(1)