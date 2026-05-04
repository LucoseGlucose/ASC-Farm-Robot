#include "Flow.h"

#include <Arduino.h>

void FlowBegin()
{
    pinMode(pinFlowSensor, INPUT_PULLUP);
}

float FlowGetRateLpS()
{
    float tOn = pulseIn(pinFlowSensor, HIGH);
    float tOff = pulseIn(pinFlowSensor, LOW);
    float periodUs = tOn + tOff;
    float freq = 1000000.0 / periodUs;

    return (freq / 7.5f) / 60.f;
}
