#include "Motors.h"

#include <Arduino.h>
#include "Commands.h"

Motor motorUpperArm = Motor(7, 0, 90, 0);
Motor motorArmJoint = Motor(6, 45, 90, 90);
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
    pinMode(pinMotorRelay, OUTPUT);
    
    for (int i = 0; i < 6; i++)
    {
        motors[i].Setup();
    }
}

void MotorsAttach()
{
    digitalWrite(pinMotorRelay, HIGH);

    for (int i = 5; i > -1; i--)
    {
        motors[i].Attach();
        delay(400);
    }
}

void MotorsDetach()
{
    digitalWrite(pinMotorRelay, LOW);

    for (int i = 0; i < 6; i++)
    {
        motors[i].Detach();
    }
}

void MotorsHome()
{
    for (int i = 0; i < 6; i++)
    {
        motors[i].Home();
    }
}

void MotorsMoveToPos(float x, float y, float z, float time)
{
    float y2 = y * y;
    float zFromTop = z - 7.4;
    float zFT2 = zFromTop * zFromTop;

    float ua = asin((y2 + zFT2 + 8.79) / (12.32 * sqrtf(y2 + zFT2))) - atan2(7.4 - z, y) + 5.59;
    float aj = acos((y2 + zFT2 - 67.11) / 66.53) + 11.87;
    float la = asin(x / 4.36);
    float w = 90 - aj;

    float yBottomFront = y - 1.5 * cos(aj + ua - 90);
    float yBottomBack = 7.4 - 6.16 * cos(ua) - 1.3 / cos(180 - aj + ua);

    float servoAngleUA = ua + 45;
    float servoAngleAJ = aj + 70;
    float servoAngleLA = la + 110;
    float servoAngleW = w + 90;
    
    if (yBottomFront < .25 || yBottomBack < .25)
    {
        return;
    }
    
    CommandSend(String(servoAngleUA) + " - " + String(servoAngleAJ) + " - " + String(servoAngleLA) + " - " + String(servoAngleW) + " - " + String(yBottomFront) + " - " + String(yBottomBack));

    if (time < .01f)
    {
        motorWrist.Move(servoAngleW);
        motorLowerArm.Move(servoAngleLA);
        motorArmJoint.Move(servoAngleAJ);
        motorUpperArm.Move(servoAngleUA);
    }
    else 
    {
        motorWrist.Move(servoAngleW, time);
        motorLowerArm.Move(servoAngleLA, time);
        motorArmJoint.Move(servoAngleAJ, time);
        motorUpperArm.Move(servoAngleUA, time);
    }
}
