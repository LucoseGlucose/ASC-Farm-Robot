#include <Servo.h>

struct Motor
{
    Servo servo;
    const int pin;
    const int minAngle;
    const int maxAngle;
    const int homeAngle;

    Motor(const int pin, const int minAngle, const int maxAngle, const int homeAngle);
    void Setup();
    void Attach();
    void Detach();
    void Home();
    void Move(int angle);
    void Move(int angle, float time);
    void Move(int startAngle, int angle, float time);
};

extern Motor motorUpperArm;
extern Motor motorArmJoint;
extern Motor motorLowerArm;
extern Motor motorWrist;
extern Motor motorEntranceGate;
extern Motor motorExitGate;
extern Motor motors[6];

const int pinMotorRelay = 49;

void MotorsBegin();
void MotorsAttach();
void MotorsDetach();
void MotorsHome();