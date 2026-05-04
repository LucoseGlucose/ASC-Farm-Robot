import time
import enum
from Commands import SerialCommands
from Commands import Command
from Visits import Visit
import Visits
import datetime
import gpiozero

class SystemState(enum.IntEnum):
    STARTUP = 1
    IDLE = 2
    ENTERING = 3
    PREPARING = 4
    MILKING = 5
    CLEANING = 6
    EXITING = 7
    STOPPED = 8

currentState: SystemState = SystemState.STOPPED

def SwitchState(newState: SystemState):
    global currentState
    currentState = newState
    serialToLaptop.Send('U', str(newState.value))
    print("State changed to: " + newState.name)

def EStop():
    SwitchState(SystemState.STOPPED)

estop: gpiozero.Button = gpiozero.Button(4)
estop.when_deactivated = EStop

serialToLaptop: SerialCommands = SerialCommands("/dev/ttyS0", 19200, ';')
serialToArduino: SerialCommands = SerialCommands("/dev/ttyACM0", 19200, ';')

while not serialToLaptop.serialPort.is_open:
    print("Please connect laptop")
    serialToLaptop.serialPort.open()
    time.sleep(1)

while not serialToArduino.serialPort.is_open:
    print("Please connect arduino")
    serialToArduino.serialPort.open()
    time.sleep(1)

Visits.LoadVisits()

currentVisit: Visit | None = None
milkTime: datetime.datetime = datetime.datetime.now()

serialToLaptop.Send('U', "Raspberry Pi Ready")
print("Raspberry Pi Ready")

while True:
    match currentState:
        case SystemState.STOPPED:
            command: Command = serialToArduino.ReadCommand()
            
            if command.prefix != '':
                SwitchState(SystemState.STARTUP)

        case SystemState.STARTUP:
            command: Command = serialToArduino.ReadCommand()
            
            if command.prefix == 'U' and command.message == "IDLE":
                SwitchState(SystemState.IDLE)

        case SystemState.IDLE:
            serialToLaptop.Send('T', str((datetime.datetime.now() - milkTime).seconds))
            
            command: Command = serialToArduino.ReadCommand()

            if command.prefix == 'G':
                serialToLaptop.SendCommand(command)

            if command.prefix == 'R':
                print(command.message)
                lastVisit: Visit = next((visit for visit in iter(Visits.visitList) if visit.cowID == command.message), Visit("", datetime.datetime.min, 0))
                
                if lastVisit.time + Visits.minTimeBetweenMilks > datetime.datetime.now():
                    print("Cow ID:" + command.message + " milking too soon")
                    serialToArduino.Send('U', "IDLE")
                    continue
                
                currentVisit = Visit(command.message, datetime.datetime.now(), 0)
                serialToLaptop.Send('R', currentVisit.cowID)
                
                serialToArduino.Send('U', "ENTERING")
                SwitchState(SystemState.ENTERING)

        case SystemState.ENTERING:
            command: Command = serialToArduino.ReadCommand()

            if command.prefix == 'G':
                serialToLaptop.SendCommand(command)
                
            if command.prefix == 'D':
                print(command.message)
                serialToLaptop.SendCommand(command)

            if command.prefix == 'U':
                if command.message == "PREPARING":
                    SwitchState(SystemState.PREPARING)
                elif command.message == "IDLE":
                    currentVisit = Visit("", datetime.datetime.min, 0)
                    SwitchState(SystemState.IDLE)

        case SystemState.PREPARING:
            command: Command = serialToArduino.ReadCommand()

            if command.prefix == 'D':
                serialToLaptop.SendCommand(command)
                print(command.message)

            if command.prefix == 'U' and command.message == "MILKING":
                milkTime = datetime.datetime.now()
                SwitchState(SystemState.MILKING)
            
        case SystemState.MILKING:
            milkDuration: datetime.timedelta = datetime.datetime.now() - milkTime
            serialToLaptop.Send('T', str(milkDuration.seconds))
            
            command: Command = serialToArduino.ReadCommand()
            if command.prefix == 'F':
                flow: float = float(command.message)
                currentVisit.milkVolume += flow

                serialToLaptop.SendCommand(command)
                print(flow)

            if command.prefix == 'U' and command.message == "CLEANING":
                Visits.visitList.appendleft(currentVisit)
                Visits.SaveVisits()
                
                currentVisit = Visit("", datetime.datetime.min, 0)
                milkTime = datetime.datetime.now()
                
                SwitchState(SystemState.CLEANING)
                print("Done Milking")

        case SystemState.CLEANING:
            command: Command = serialToArduino.ReadCommand()
            if command.prefix == 'U' and command.message == "EXITING":
                SwitchState(SystemState.EXITING)

        case SystemState.EXITING:
            command: Command = serialToArduino.ReadCommand()

            if command.prefix == 'G':
                serialToLaptop.SendCommand(command)
                
            if command.prefix == 'U' and command.message == "IDLE":
                SwitchState(SystemState.IDLE)

        case _:
            continue
