#include "RFID.h"
#include "Motors.h"
#include "Commands.h"
#include "Distance.h"
#include "Arm.h"
#include "Laser.h"
#include "Flow.h"

const int pinEStop = 22;
const int pinResetBtn = 23;

enum class SystemState
{
    STARTUP,
    IDLE,
    ENTERING,
    PREPARING,
    MILKING,
    CLEANING,
    EXITING,
    STOPPED,
};

volatile SystemState currentState = SystemState::STOPPED;

unsigned long enterStartTimeMs = 0;
unsigned long enterMaxDurationMs = 20 * 1000;

const float minYCoord = 1.f;
float uaMilkAngle;
float milkXCoord;

unsigned long milkStartTimeMs = 0;
unsigned long milkMinDurationMs = 5 * 1000;

const int pinPumpFromCow = 44;
const int pinPumpToCow = 45;

void EmergencyStop()
{
    currentState = SystemState::STOPPED;

    MotorsDetach();
    LaserStop();
}

void setup()
{
    CommandsBegin();
    RFIDBegin();
    MotorsBegin();
    DistanceBegin();
    LaserBegin();
    FlowBegin();

    pinMode(pinEStop, INPUT_PULLUP);
    pinMode(pinResetBtn, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(pinEStop), EmergencyStop, FALLING);
}

void loop()
{
    switch (currentState)
    {
        case SystemState::STOPPED:
        {
            if (digitalRead(pinResetBtn) == LOW)
            {
                currentState = SystemState::STARTUP;
                CommandSend("USTARTUP");
            }

            break;
        }
        case SystemState::STARTUP:
        {
            MotorsHome();
            MotorsAttach();
            
            currentState = SystemState::IDLE;
            CommandSend("UIDLE");
            break;
        }
        case SystemState::IDLE:
        {
            String cowID = RFIDRead();
            
            if (cowID != "")
            {
                CommandSend("R" + cowID);
                delay(250);
            }

            String command = CommandRead();

            if (command != "" && command[0] == 'U')
            {
                String message = command.substring(1);

                if (message == "ENTERING")
                {
                    motorEntranceGate.Move(motorEntranceGate.homeAngle, motorEntranceGate.minAngle, 2.f);

                    enterStartTimeMs = millis();
                    currentState = SystemState::ENTERING;
                }
            }

            break;
        }
        case SystemState::ENTERING:
        {
            if (millis() - enterStartTimeMs  > enterMaxDurationMs)
            {
                currentState = SystemState::IDLE;
                motorEntranceGate.Move(motorEntranceGate.minAngle, motorEntranceGate.homeAngle, 3.f);

                CommandSend("UIDLE");
                break;
            }
            
            float iterations = 3;
            float totalDistance = 0.f;
            
            for (int i = 0; i < iterations; i++)
            {
                totalDistance += DistanceGetCm();
                delay(60);
            }

            float averageDistance = totalDistance / iterations;
            CommandSend("D" + String(averageDistance));

            if (averageDistance > 2.f && averageDistance < distanceWithCow)
            {
                currentState = SystemState::PREPARING;
                motorEntranceGate.Move(motorEntranceGate.minAngle, motorEntranceGate.homeAngle, 3.f);

                CommandSend("UPREPARING");
            }

            break;
        }
        case SystemState::PREPARING:
        {
            float uaGroundEndAngle = 40;
            ArmMoveHorizontal(minYCoord, motorUpperArm.homeAngle, uaGroundEndAngle, 2.f);
            delay(200);

            float aj = ArmCalcAJFromYCoord(minYCoord, uaGroundEndAngle);
            milkXCoord = ArmCalcXCoord(uaGroundEndAngle, aj);

            CommandSend(String(aj));
            CommandSend(String(milkXCoord));

            LaserStart();
            uaMilkAngle = 43;

            for (float i = uaGroundEndAngle; i < 43; i += .5f)
            {
                unsigned short distMm = LaserReadMm();
                if (distMm < laserMinDistanceMm)
                {
                    uaMilkAngle = i;
                    break;
                }

                ArmMoveVertical(milkXCoord, i, i + .5f, .5f);
            }

            digitalWrite(pinPumpFromCow, HIGH);
            digitalWrite(pinPumpToCow, HIGH);

            LaserStop();
            currentState = SystemState::MILKING;
            CommandSend("UMILKING");
            
            milkStartTimeMs = millis();
            break;
        }
        case SystemState::MILKING:
        {
            float flow = FlowGetRateLpS();
            CommandSend("F" + String(flow));

            if (flow < .0001f && millis() - milkStartTimeMs > milkMinDurationMs)
            {
                digitalWrite(pinPumpFromCow, LOW);
                digitalWrite(pinPumpToCow, LOW);

                currentState = SystemState::CLEANING;
                CommandSend("UCLEANING");
            }
            
            break;
        }
        case SystemState::CLEANING:
        {
            float uaUpEndAngle = 40;
            ArmMoveVertical(milkXCoord, uaMilkAngle, uaUpEndAngle, .5f);
            
            delay(200);
            ArmMoveHorizontal(minYCoord, uaUpEndAngle, motorUpperArm.homeAngle, 2.f);

            MotorsHome();
            
            currentState = SystemState::EXITING;
            CommandSend("UEXITING");

            break;
        }
        case SystemState::EXITING:
        {
            motorExitGate.Move(motorExitGate.homeAngle, motorExitGate.maxAngle, 1.f);

            float iterations = 5;
            float totalDistance = 0.f;

            for (int i = 0; i < iterations; i++)
            {
                totalDistance += DistanceGetCm();
                delay(60);
            }

            float averageDistance = totalDistance / iterations;
            CommandSend("D" + String(averageDistance));

            if (averageDistance > 2.f && averageDistance > distanceWithCow)
            {
                motorEntranceGate.Move(motorEntranceGate.maxAngle, motorEntranceGate.homeAngle, 3.f);
                
                currentState = SystemState::IDLE;
                CommandSend("UIDLE");
            }

            break;
        }
    }
}