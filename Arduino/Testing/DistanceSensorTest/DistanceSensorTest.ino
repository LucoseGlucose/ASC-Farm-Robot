

const int pinDistanceTrigger = 47;
const int pinDistanceEcho = 46;

void setup()
{
    Serial.begin(19200);

    pinMode(pinDistanceTrigger, OUTPUT);
    pinMode(pinDistanceEcho, INPUT);
}

void loop()
{
    digitalWrite(pinDistanceTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pinDistanceTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinDistanceTrigger, LOW);

    float duration = pulseIn(pinDistanceEcho, HIGH);
    float dist = (duration * .0343f) / 2.f;

    Serial.print(dist);
    Serial.println(" cm");
}