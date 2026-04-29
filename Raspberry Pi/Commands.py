import serial

commandBaudRate = 19200
commandTerminator = ';'
commandSerial: serial.Serial

def CommandsBegin():
    commandSerial = serial.Serial("/dev/ttyACM0", commandBaudRate, timeout=1)
    commandSerial.reset_input_buffer()

def CommandRead() -> str:
    return commandSerial.read_until(commandTerminator.encode()).decode()

def CommandSend(prefix: str, command: str):
    commandSerial.write((prefix + command + commandTerminator).encode())