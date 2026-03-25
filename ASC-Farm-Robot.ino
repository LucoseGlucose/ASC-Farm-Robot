
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\0');
        
        if (command == "off")
        {
            digitalWrite(LED_BUILTIN, LOW);
        }

        if (command == "on")
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }
    }
}