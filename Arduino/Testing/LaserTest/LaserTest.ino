#include <Wire.h>
#include <VL53L0X.h>

VL53L0X laser = VL53L0X();

void setup()
{
    Serial.begin(19200);
    Wire.begin();
    laser.setTimeout(500);
    laser.init();
    laser.startContinuous();
}

void loop()
{
    Serial.println(laser.readRangeContinuousMillimeters());
}