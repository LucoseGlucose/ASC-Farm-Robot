#include "Commands.h"

void CommandsBegin()
{
    Serial.begin(commandBaudRate);
}

String CommandRead()
{
    if (!Serial.available())
    {
        return "";
    }

    return Serial.readStringUntil(commandTerminator);
}

void CommandSend(String command)
{
    Serial.print(command + commandTerminator);
}
