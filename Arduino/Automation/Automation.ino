#include "RFID.h"
#include "Motors.h"
#include "Commands.h"

const int pinEStop = 2;
const int pinResetBtn = 4;

const int gateOpenAngle = 15;

enum class SystemState
{
    STARTUP,
    IDLE,
    MOVING,
    MILKING,
    STOPPED,
};

volatile SystemState currentState = SystemState::STARTUP;

void EmergencyStop()
{
    currentState = SystemState::STOPPED;
    MotorsDetach();
}

void setup()
{
    CommandsBegin();
    RFIDBegin();

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
            }

            break;
        }
        case SystemState::STARTUP:
        {
            MotorsBegin();
            currentState = SystemState::IDLE;
            break;
        }
        case SystemState::IDLE:
        {
            String command = CommandRead();

            if (command != "")
            {
                Serial.println(command);
                char prefix = command[0];
                
                switch (prefix)
                {
                case 'O':
                    MotorMove(servoEntranceGate, gateOpenAngle);
                    delay(5000);
                    MotorMove(servoEntranceGate, 90);
                    break;
                }
            }

            String cowID = RFIDRead();
            
            if (cowID != "")
            {
                CommandSend('C', cowID);
            }

            break;
        }
        default:
        {
            break;
        }
    }
}