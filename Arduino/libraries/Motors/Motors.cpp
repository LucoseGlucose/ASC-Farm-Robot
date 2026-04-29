#include "Motors.h"

#include <Arduino.h>

Servo servoUpperArm = Servo();
Servo servoArmjoint = Servo();
Servo servoLowerArm = Servo();
Servo servoPitch = Servo();
Servo servoYaw = Servo();

Servo servoEntranceGate = Servo();
Servo servoExitGate = Servo();

void MotorsBegin()
{
    servoUpperArm.attach(pinServoUpperArm);
    servoArmjoint.attach(pinServoArmjoint);
    servoLowerArm.attach(pinServoLowerArm);
    servoPitch.attach(pinServoPitch);
    servoYaw.attach(pinServoYaw);

    servoEntranceGate.attach(pinServoEntranceGate);
    servoExitGate.attach(pinServoExitGate);
}

void MotorsDetach()
{
    servoUpperArm.detach();
    servoArmjoint.detach();
    servoLowerArm.detach();
    servoPitch.detach();
    servoYaw.detach();

    servoEntranceGate.detach();
    servoExitGate.detach();
}

void MotorMove(Servo servo, int angle)
{
    servo.write(angle);
}

void MotorMove(Servo servo, int angle, float time)
{
    int delta = angle - servo.read();
    for (int i = servo.read(); i != angle; (delta > 0) ? i++ : i--)
    {
        servo.write(i);
        delay(1000 * time / delta);
    }
}
