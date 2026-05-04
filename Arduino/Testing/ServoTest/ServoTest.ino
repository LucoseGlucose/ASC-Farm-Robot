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
      float angle1 = msg.substring(0, index1).toFloat();

      msg = msg.substring(index1 + 1);
      int index2 = msg.indexOf(',');
      float angle2 = msg.substring(0, index2).toFloat();

      float angle3 = msg.substring(index2 + 1).toFloat();

      Serial.print(String(angle1) + ", " + String(angle2) + ", " + String(angle3));
      servo1.writeMicroseconds(map(angle1, 0, 180, 544, 2400));
      servo2.writeMicroseconds(map(angle2, 0, 180, 544, 2400));
      servo3.writeMicroseconds(map(angle3, 0, 180, 544, 2400));
    }
  }
}

void Move(Servo servo, float startAngle, float angle, float time)
{
  servo.writeMicroseconds(map(startAngle, 0, 180, 544, 2400));
  
  float delta = angle - startAngle;

  if (delta < .1f)
  {
    return;
  }
  
  Serial.println(delta);
  float unsignedDelta = abs(delta);
  Serial.println(unsignedDelta);
  int direction = delta / unsignedDelta;
  Serial.println(direction);

  for (float i = startAngle; i - angle < .05f; i += direction * .1f)
  {
    Serial.println(i);
    servo.writeMicroseconds(map(i, 0, 180, 544, 2400));
    delay(100.f * time / unsignedDelta);
  }

  Serial.println("Done");
}