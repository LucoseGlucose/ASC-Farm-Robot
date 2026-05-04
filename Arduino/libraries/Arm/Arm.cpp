#include "Arm.h"

#include <Arduino.h>
#include "Motors.h"
#include "Commands.h"

float ArmCalcAJFromYCoord(float y, float uaAngle)
{
    return 162 - degrees(asin((y - 7.4f + 6.13f * cos(radians(45 - uaAngle))) / -5.62f) - radians(45 - uaAngle) + .5 * PI);
}

float ArmCalcAJFromXCoord(float x, float uaAngle)
{
    return 162 - degrees(asin((x + 6.13f * sin(radians(45 - uaAngle))) / 5.62f) - radians(45 - uaAngle));
}

float ArmCalcXCoord(float uaAngle, float ajAngle)
{
    return -6.13f * sin(radians(45 - uaAngle)) + 5.62f * cos(radians((45 - uaAngle) + (162 - ajAngle) - 90));
}

float ArmCalcYCoord(float uaAngle, float ajAngle)
{
    return -6.13f * cos(radians(45 - uaAngle)) - 5.62f * sin(radians((45 - uaAngle) + (162 - ajAngle) - 90)) + 7.4f;
}

void ArmMoveHorizontal(float y, float startAngle, float endAngle, float time)
{
    if (y < .5f)
    {
        return;
    }

    motorUpperArm.Move(startAngle);
    float delta = endAngle - startAngle;

    if (delta < .1f)
    {
        return;
    }

    float unsignedDelta = abs(delta);
    int direction = delta / unsignedDelta;
    CommandSend(String(delta));

    for (float i = startAngle; (int)(i * 10) != (int)(endAngle * 10); i += .1f * direction)
    {
        CommandSend(String(i));
        motorUpperArm.MovePrecise(i);

        float armJointAngle = ArmCalcAJFromYCoord(y, i);
        motorArmJoint.MovePrecise(armJointAngle);

        CommandSend(String(i) + ", " + String(armJointAngle));
        delay(100.f * time / unsignedDelta);
    }
}

void ArmMoveVertical(float x, float startAngle, float endAngle, float time)
{
    motorUpperArm.Move(startAngle);
    float delta = endAngle - startAngle;

    if (delta < .1f)
    {
        return;
    }

    float unsignedDelta = abs(delta);
    int direction = delta / unsignedDelta;
    CommandSend(String(delta));

    for (float i = startAngle; (int)(i * 10) != (int)(endAngle * 10); i += .1f * direction)
    {
        CommandSend(String(i));
        motorUpperArm.MovePrecise(i);

        float armJointAngle = ArmCalcAJFromXCoord(x, i);
        motorArmJoint.MovePrecise(armJointAngle);
        motorWrist.MovePrecise(180 - i);

        CommandSend(String(i) + ", " + String(armJointAngle));
        delay(100.f * time / unsignedDelta);
    }
}
