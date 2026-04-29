#include "Motors.h"

void MotorsBegin()
{
    servoUpperArm.attach(pinServoUpperArm);
    servoArmjoint.attach(pinServoArmjoint);
    servoLowerArm.attach(pinServoLowerArm);
    servoPitch.attach(pinServoPitch);
    servoYaw.attach(pinServoYaw);
}

void MotorsDetach()
{
    servoUpperArm.detach();
    servoArmjoint.detach();
    servoLowerArm.detach();
    servoPitch.detach();
    servoYaw.detach();
}
