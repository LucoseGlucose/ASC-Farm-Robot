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
      servo1.attach(2);
      Serial.println("Attached");
    }
    else
    {
      float angle1 = msg.toFloat();

      Serial.println(angle1);
      servo1.write(angle1);
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