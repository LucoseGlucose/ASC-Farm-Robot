#include <Arduino.h>

const int commandBaudRate = 19200;
const char commandTerminator = ';';

void CommandsBegin();
String CommandRead();
void CommandSend(char prefix, String command);