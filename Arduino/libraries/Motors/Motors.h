#include <Servo.h>

const int pinServoUpperArm = 22;
const int pinServoArmjoint = 23;
const int pinServoLowerArm = 24;
const int pinServoPitch = 25;
const int pinServoYaw = 26;

const int pinServoEntranceGate = 27;
const int pinServoExitGate = 28;

extern Servo servoUpperArm;
extern Servo servoArmjoint;
extern Servo servoLowerArm;
extern Servo servoPitch;
extern Servo servoYaw;

extern Servo servoEntranceGate;
extern Servo servoExitGate;

void MotorsBegin();
void MotorsDetach();
void MotorMove(Servo servo, int angle);
void MotorMove(Servo servo, int angle, float time);