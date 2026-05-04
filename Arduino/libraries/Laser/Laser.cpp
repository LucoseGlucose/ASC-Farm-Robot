#include "Laser.h"

VL53L0X laser = VL53L0X();

void LaserBegin()
{
    Wire.begin();
    laser.setTimeout(500);
    laser.init();
}

void LaserStart()
{
    laser.startContinuous();
}

float LaserReadMm()
{
    return laser.readRangeContinuousMillimeters();
}

void LaserStop()
{
    laser.stopContinuous();
}
