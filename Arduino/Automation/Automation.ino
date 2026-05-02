#include "RFID.h"
#include "Motors.h"
#include "Commands.h"
#include "Distance.h"

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
                    motorEntranceGate.Move(motorEntranceGate.minAngle, 2.f);

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
                motorEntranceGate.Move(motorEntranceGate.homeAngle, 3.f);

                CommandSend("UIDLE");
            }
            
            int iterations = 5;
            float totalDistance = 0.f;
            
            for (int i = 0; i < iterations; i++)
            {
                totalDistance += DistanceGetCm();
            }
            
            if (totalDistance / (float)iterations < distanceWithCow)
            {
                currentState = SystemState::PREPARING;
                motorEntranceGate.Move(motorEntranceGate.homeAngle, 3.f);

                CommandSend("UPREPARING");
            }

            break;
        }
        default:
        {
            break;
        }
    }
}