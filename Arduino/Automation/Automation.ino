#include "RFID.h"
#include "Motors.h"
#include "Commands.h"
#include "Distance.h"
#include "Arm.h"

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

void EmergencyStop()
{
    currentState = SystemState::STOPPED;
    MotorsDetach();
}

void setup()
{
    CommandsBegin();
    RFIDBegin();
    MotorsBegin();
    DistanceBegin();

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

                float uaGroundEndAngle = 40;
                float minYCoord = 1.f;
                ArmMoveHorizontal(minYCoord, motorUpperArm.homeAngle, uaGroundEndAngle, 2.f);
                delay(200);

                float uaUpEndAngle = 41;
                float aj = ArmCalcAJFromYCoord(minYCoord, uaGroundEndAngle);
                float x = ArmCalcXCoord(uaGroundEndAngle, aj);
                
                CommandSend(String(aj));
                CommandSend(String(x));
                ArmMoveVertical(x, uaGroundEndAngle, uaUpEndAngle, 2.f);
            }

            break;
        }
        case SystemState::PREPARING:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}