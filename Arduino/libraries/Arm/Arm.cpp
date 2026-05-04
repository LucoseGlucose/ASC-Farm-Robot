#include "Arm.h"

#include <Arduino.h>
#include "Motors.h"
#include "Commands.h"

void ArmMoveAlongGround(float y, int startAngle, int endAngle, float time)
{
    if (y < .5f)
    {
        return;
    }

    motorUpperArm.Move(startAngle);

    int delta = endAngle - startAngle;
    int unsignedDelta = abs(delta);
    int direction = delta / unsignedDelta;
    
    for (int i = startAngle; i != endAngle; i += direction)
    {
        motorUpperArm.Move(i);

        float armJointAngle = 162 - degrees(asin((y - 7.4f + 6.13f * cos(radians(45 - i))) / -5.62f) - radians(45 - i) + .5 * PI);
        motorArmJoint.Move((int)ceil(armJointAngle));

        CommandSend(String(i) + ", " + String((int)ceil(armJointAngle)));
        delay(1000.f * time / (float)unsignedDelta);
    }
    
}