#include <Servo.h>

// Upper arm, home is 45, top is 0, bottom is 90
// Arm joint home is 70, top is 90, bottom is 45
// Lower arm home is 110, right is 160, left is 75
// Gray gate closed is 115 open is 0
// White gate closed is 120 open is 180

Servo servo1;
Servo servo2;
Servo servo3;

void setup()
{
  Serial.begin(19200);
}

void loop()
{
  if (Serial.available())
  {
    String msg = Serial.readString();

    if (msg.startsWith("stop"))
    {
      servo1.detach();
      servo2.detach();
      servo3.detach();
      Serial.println("Detached");
    }
    else if (msg.startsWith("start"))
    {
      servo1.attach(7);
      servo2.attach(6);
      servo3.attach(5);
      Serial.println("Attached");
    }
    else
    {
      int index1 = msg.indexOf(',');
      int angle1 = msg.substring(0, index1).toInt();

      msg = msg.substring(index1 + 1);
      int index2 = msg.indexOf(',');
      int angle2 = msg.substring(0, index2).toInt();

      int angle3 = msg.substring(index2 + 1).toInt();

      Serial.print(String(angle1) + ", " + String(angle2) + ", " + String(angle3));
      servo1.write(angle1);
      servo2.write(angle2);
      servo3.write(angle3);
    }
  }
}

void Move(Servo servo, int startAngle, int angle, float time)
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