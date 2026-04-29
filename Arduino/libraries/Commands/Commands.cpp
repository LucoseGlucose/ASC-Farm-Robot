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

void CommandSend(char prefix, String command)
{
    Serial.print(prefix + command + commandTerminator);
}
