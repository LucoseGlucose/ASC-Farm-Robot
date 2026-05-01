import time
import enum
from Commands import SerialCommands
from Commands import Command
from Visit import Visit
from Visit import visitList
from Visit import minTimeBetweenMilks
from Visit import LoadVisits
from Visit import SaveVisits
import datetime
import gpiozero # pyright: ignore[reportMissingTypeStubs]

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
    serialToLaptop.Send('U', newState.name)

def EStop():
    SwitchState(SystemState.STOPPED)

estop: gpiozero.Button = gpiozero.Button(4)
estop.when_deactivated = EStop

serialToLaptop: SerialCommands = SerialCommands("/dev/ttyS0", 19200, ';')
serialToArduino: SerialCommands = SerialCommands("/dev/ttyACM0", 19200, ';')

while not serialToLaptop.serialPort.is_open:
    print("Please connect laptop with serial")
    serialToLaptop.serialPort.open()
    time.sleep(1)

while not serialToArduino.serialPort.is_open:
    serialToLaptop.Send('E', "Please connect laptop")
    serialToArduino.serialPort.open()
    time.sleep(1)

LoadVisits()

currentVisit: Visit | None = None
serialToLaptop.Send('U', "Raspberry Pi Ready")

while True:
    match currentState:
        case SystemState.STOPPED:
            command: Command = serialToArduino.ReadCommand()
            
            if command.prefix != '':
                SwitchState(SystemState.STARTUP)

        case SystemState.STARTUP: # pyright: ignore[reportUnnecessaryComparison]
            command: Command = serialToArduino.ReadCommand()
            
            if command.prefix == 'U' and command.message == "IDLE":
                SwitchState(SystemState.IDLE)

        case SystemState.IDLE: # pyright: ignore[reportUnnecessaryComparison]
            command: Command = serialToArduino.ReadCommand()

            if command.prefix == 'R':
                lastVisit: Visit = next((visit for visit in iter(visitList) if visit.cowID == command.message), Visit("", datetime.datetime.min, 0))
                
                if lastVisit.time + minTimeBetweenMilks > datetime.datetime.now():
                    serialToLaptop.Send('R', "Cow ID:" + command.message + " milking too soon")
                    serialToArduino.Send('U', "IDLE")
                    continue
                
                currentVisit = Visit(command.message, datetime.datetime.now(), 0)
                serialToLaptop.Send('R', currentVisit.cowID)

                visitList.appendleft(currentVisit)
                SaveVisits()
                
                serialToArduino.Send('U', "ENTERING")
                SwitchState(SystemState.ENTERING)

        case SystemState.ENTERING: # pyright: ignore[reportUnnecessaryComparison]
            command: Command = serialToArduino.ReadCommand()

            if command.prefix == 'U' and command.message == "PREPARING":
                SwitchState(SystemState.PREPARING)

        case SystemState.PREPARING: # pyright: ignore[reportUnnecessaryComparison]

            pass
            
        case _:
            continue
