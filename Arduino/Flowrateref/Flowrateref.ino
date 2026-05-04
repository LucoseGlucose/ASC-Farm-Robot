//Reference Code
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
#define pulse_ip 7

unsigned long ontime, offtime;
float freq, period;
int duty;

void setup() {
pinMode(pulse_ip, INPUT);
lcd.begin(16, 4);
lcd.print("Freq:");
}

void loop() {
ontime = pulseIn(pulse_ip, HIGH);
offtime = pulseIn(pulse_ip, LOW);
period = ontime + offtime; // in microseconds
freq = 1000000.0 / period;
duty = (ontime / period) * 100;

lcd.setCursor(5, 0);
lcd.print(freq);
lcd.print("Hz");
delay(500);
}
