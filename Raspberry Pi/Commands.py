import serial

class Command:
    prefix: str
    message: str
    terminator: str

    def __init__(self, prefix: str, message: str, terminator: str):
        self.prefix = prefix
        self.message = message
        self.terminator = terminator

    def FullMessage(self) -> str:
        return self.prefix + self.message + self.terminator

class SerialCommands:
    baudRate: int
    terminator: str
    serialPort: serial.Serial

    def __init__(self, portName: str, baudRate: int, terminator: str):
        self.baudRate = baudRate
        self.terminator = terminator
        
        self.serialPort = serial.Serial(portName, baudRate)
        self.serialPort.reset_input_buffer()

    def Read(self) -> str:
        if self.Available() < 1:
            return ""
        
        return self.serialPort.read_until(self.terminator.encode()).decode()

    def ReadCommand(self) -> Command:
        command: str = self.Read()

        if len(command) < 1:
            return Command('', "", '')
        
        return Command(command[0], command[1:len(command) - 2], command[len(command) - 1])

    def Send(self, prefix: str, command: str):
        self.serialPort.write((prefix + command + self.terminator).encode())

    def SendCommand(self, command: Command):
        self.serialPort.write(command.FullMessage().encode())

    def Available(self) -> int:
        return self.serialPort.in_waiting