import Commands

while True:
    if command := Commands.CommandRead() != "":
        print(command)