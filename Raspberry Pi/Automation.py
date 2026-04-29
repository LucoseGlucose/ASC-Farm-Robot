import time
import Commands

Commands.CommandsBegin()
time.sleep(1)

while True:
    if command := Commands.CommandRead() != "":
        print(command)
    if input("Poop please") == "O":
        Commands.CommandSend('O', "")