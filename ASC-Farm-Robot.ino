#include <Servo.h>

Servo servo = Servo();

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    servo.attach(9);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    
    for (int i = 0; i < 180; i++)
    {
        servo.write(i);
        delay(5);
    }

    digitalWrite(LED_BUILTIN, LOW);

    for (int i = 180; i > 0; i--)
    {
        servo.write(i);
        delay(5);
    }
}