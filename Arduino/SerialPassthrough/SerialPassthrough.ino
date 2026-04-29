#include <SoftwareSerial.h>

SoftwareSerial serialFromPi = SoftwareSerial(3, 2);

void setup()
{
    serialFromPi.begin(19200);
    Serial.begin(19200);
}

void loop()
{
    unsigned int piToLaptopSize = serialFromPi.available();

    if (piToLaptopSize > 0)
    {
        String piToLaptop = serialFromPi.readString();
        Serial.write(piToLaptop.c_str());
    }

    unsigned int laptopToPiSize = Serial.available();

    if (laptopToPiSize > 0)
    {
        String laptopToPi = Serial.readString();
        serialFromPi.write(laptopToPi.c_str());
    }
}