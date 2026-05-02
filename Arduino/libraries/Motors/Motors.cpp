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

    float ua = asin((y2 + zFT2 + 8.79) / (12.32 * sqrtf(y2 + zFT2))) - atan2(7.4 - z, y) + radians(5.59);
    float aj = acos((y2 + zFT2 - 67.11) / 66.53) + radians(11.87);
    float la = asin(x / 4.36);
    float w = PI * .5 - aj;

    float yBottomFront = y - 1.5 * cos(aj + ua - PI * .5);
    float yBottomBack = 7.4 - 6.16 * cos(ua) - 1.3 / cos(PI - aj + ua);

    float servoAngleUA = degrees(ua) + 45;
    float servoAngleAJ = degrees(aj) + 70;
    float servoAngleLA = degrees(la) + 110;
    float servoAngleW = degrees(w) + 90;

    CommandSend(String(servoAngleUA) + " - " + String(servoAngleAJ) + " - " + String(servoAngleLA) + " - " + String(servoAngleW) + " - " + String(yBottomFront) + " - " + String(yBottomBack));

    if (time < .01f)
    {
        motorUpperArm.Move(servoAngleUA);
        motorArmJoint.Move(servoAngleAJ);
        motorLowerArm.Move(servoAngleLA);
        motorWrist.Move(servoAngleW);
    }
    else 
    {
        motorUpperArm.Move(servoAngleUA, time);
        motorArmJoint.Move(servoAngleAJ, time);
        motorLowerArm.Move(servoAngleLA, time);
        motorWrist.Move(servoAngleW, time);
    }
}
