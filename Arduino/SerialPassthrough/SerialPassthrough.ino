#include <SoftwareSerial.h>

SoftwareSerial serialFromPi = SoftwareSerial(3, 2);

void setup()
{
    serialFromPi.begin(19200);
    Serial.begin(19200);
}

void loop()
{
    if (serialFromPi.available())
    {
        Serial.print(serialFromPi.readString());
    }

    if (Serial.available())
    {
        serialFromPi.print(Serial.readString());
    }
}