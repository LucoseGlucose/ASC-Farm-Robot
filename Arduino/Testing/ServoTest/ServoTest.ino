#include <Servo.h>

// Upper arm, home is 45, top is 0, bottom is 90
// Arm joint home is 70, top is 90, bottom is 45
// Lower arm home is 110, right is 160, left is 75
// Gray gate closed is 115 open is 0
// White gate closed is 120 open is 180

Servo servo;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    String msg = Serial.readString();

    if (msg.startsWith("stop"))
    {
      servo.detach();
      Serial.println("Detached");
    }
    else if (msg.startsWith("start"))
    {
      servo.attach(7);
      Serial.println("Attached");
    }
    else
    {
      int angle = msg.toInt();
      
      Serial.print(angle);
      Serial.print(" angle accepted ");
      Move(servo.read(), angle, 4.f);
    }
  }
}

void Move(int startAngle, int angle, float time)
{
  servo.write(startAngle);

  if (angle > startAngle)
  {
    for (int i = startAngle; i < angle; i++)
    {
      servo.write(i);
      delay(1000 * time / (angle - startAngle));
    }
  }
  else if (angle < startAngle)
  {
    for (int i = startAngle; i > angle; i--)
    {
      servo.write(i);
      delay(1000 * time / (startAngle - angle));
    }
  }
}