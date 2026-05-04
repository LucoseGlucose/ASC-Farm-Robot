
#include <Wire.h>
#include <VL53L0X.h>

extern VL53L0X laser;

const unsigned short laserMinDistanceMm = 100;

void LaserBegin();
void LaserStart();
float LaserReadMm();
void LaserStop();