#include <Servo.h>

// Upper arm, home is 45, top is 0, bottom is 90
// Arm joint home is 70, top is 90, bottom is 45
// Lower arm home is 110, right is 160, left is 75
// Gray gate closed is 115 open is 0
// White gate closed is 120 open is 180

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
void MotorsAttach();
void MotorsDetach();
void MotorMove(Servo servo, int angle);
void MotorMove(Servo servo, int angle, float time);