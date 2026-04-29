#include <Servo.h>

const int pinServoUpperArm = 22;
const int pinServoArmjoint = 23;
const int pinServoLowerArm = 24;
const int pinServoPitch = 25;
const int pinServoYaw = 26;

const Servo servoUpperArm = Servo();
const Servo servoArmjoint = Servo();
const Servo servoLowerArm = Servo();
const Servo servoPitch = Servo();
const Servo servoYaw = Servo();

void MotorsBegin();
void MotorsDetach();