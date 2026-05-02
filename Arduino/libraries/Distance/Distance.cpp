#include "Distance.h"

#include <Arduino.h>

void DistanceBegin()
{
    pinMode(pinDistanceTrigger, OUTPUT);
    pinMode(pinDistanceEcho, INPUT);
}

float DistanceGetCm()
{
    digitalWrite(pinDistanceTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pinDistanceTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinDistanceTrigger, LOW);

    float duration = pulseIn(pinDistanceEcho, HIGH);
    return (duration * .0343f) / 2.f;
}
