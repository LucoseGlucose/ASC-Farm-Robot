#include "Motors.h"

#include <Arduino.h>
#include "Commands.h"

Motor motorUpperArm = Motor(7, 0, 90, 0);
Motor motorArmJoint = Motor(6, 45, 95, 95);
Motor motorLowerArm = Motor(5, 75, 160, 110);
Motor motorWrist = Motor(4, 20, 140, 90);
Motor motorEntranceGate = Motor(3, 10, 120, 115);
Motor motorExitGate = Motor(2, 110, 180, 120);
Motor motors[6] = { motorUpperArm, motorArmJoint, motorLowerArm, motorWrist, motorEntranceGate, motorExitGate };

Motor::Motor(const int pin, const int minAngle, const int maxAngle, const int homeAngle)
    : servo(), pin(pin), minAngle(minAngle), maxAngle(maxAngle), homeAngle(homeAngle)
{
    
}

void Motor::Setup()
{
    pinMode(pin, OUTPUT);
}

void Motor::Attach()
{
    servo.attach(pin);
}

void Motor::Detach()
{
    servo.detach();
}

void Motor::Home()
{
    Move(homeAngle);
}

void Motor::Move(int angle)
{
    if (angle < minAngle || angle > maxAngle)
    {
        return;
    }

    servo.write(angle);
}

void Motor::Move(int angle, float time)
{
    Move(servo.read(), angle, time);
}

void Motor::Move(int startAngle, int angle, float time)
{
    if (angle < minAngle || angle > maxAngle)
    {
        return;
    }

    servo.write(startAngle);

    if (angle > startAngle)
    {
        for (int i = startAngle; i < angle; i++)
        {
            servo.write(i);
            delay(1000 * time / (angle - startAngle));
        }
    }
    else if (angle < startAngle)
    {
        for (int i = startAngle; i > angle; i--)
        {
            servo.write(i);
            delay(1000 * time / (startAngle - angle));
        }
    }
}

void MotorsBegin()
{
    digitalWrite(pinMotorRelay, HIGH);
    pinMode(pinMotorRelay, OUTPUT);
    
    for (int i = 0; i < 6; i++)
    {
        motors[i].Setup();
    }
}

void MotorsAttach()
{
    digitalWrite(pinMotorRelay, LOW);

    for (int i = 5; i > -1; i--)
    {
        motors[i].Attach();
        delay(400);
    }
}

void MotorsDetach()
{
    digitalWrite(pinMotorRelay, HIGH);

    for (int i = 0; i < 6; i++)
    {
        motors[i].Detach();
    }
}

void MotorsHome()
{
    for (int i = 5; i > -1; i--)
    {
        motors[i].Home();
    }
}