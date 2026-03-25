import serial
import time

s = serial.Serial("/dev/ttyACM0", 115200, timeout=1)
s.reset_input_buffer()

while (command := input("Enter Command: ")) != "quit":
    
    if (command == "off"):
        s.write("off\n")
    
    if (command == "on"):
        s.write("on\n")
    
    time.sleep(1)