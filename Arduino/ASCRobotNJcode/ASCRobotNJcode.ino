//Libraries
#include<Servo.h>
#include <LiquidCrystal_I2C.h>
//DAQ Inputs

//DAQ Outputs
int servoDAQ1 = 20; // DAQ output 1
int servoDAQ2 = 21; // DAQ output 2
int servoDAQ3 = 22; // DAQ output 3
int servoDAQ4 = 23; // DAQ output 4
int servoDAQ5 = 24; // DAQ output 5
int servoDAQ6 = 25; // DAQ output 6

//Inputs
int run = 34; 
int RFID = 35;

//Output
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
int pump1 = 18;
int pump2 = 19;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorDAQ, OUTPUT); //Set output to pin 21 
  //Servo pins
  servo1.attach(28);
  servo2.attach(29);
  servo3.attach(30);
  servo4.attach(31);
  servo5.attach(32);
  servo6.attach(33);

  //Initalize Inputs
  lcd.begin(16, 2);
  lcd.backlight(); // Turn on the backlight
  lcd.init();
  pinMode(run, INPUT);
  pinMode(RFID, INPUT);

  //Initalize Outputs
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);

  //Initalize Serial Communication 
  Serial.begin(9600);
  Serial.println("ASC Milk Robot ON");
  lcd.setCursor(0, 0); // Set cursor to the first row, first column
  lcd.print("ASC Milk Robot ON"); // Display the message on the first line
  wait(10000);
  }

void loop() {
  //Analog Inputs
  float dsensor = analogRead(A2); //Read distance input
  float wsensor = analogRead(A0); //Read waterflow input

  //Digital inputs
  int runi = digitalRead(run);
  int RFIDi = digitalRead(RFID);
  
  // Copy Values to DAQ
  analogWrite(dsensor, A3);
  analogWrite(wsensor, A1);

  //Variables
  float flowrate = wsensor*15;
  float volume = flowrate*13;
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;

  //Initalize Robot
  lcd.setCursor(0, 0); // Set cursor to the first row, first column
  lcd.print("Flow Rate:"); // Display the message on the first line
  lcd.print(flowrate);
  lcd.setCursor(1, 0);
  lcd.print("Volume:");
  lcd.print(volume);
  lcd.setCursor(1, 0);
  lcd.print("Status:")
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  servo6.write(0);
  digitalWrite(pump1, LOW);
  digitalWrite(pump2, LOW);

  //Main Code
  if(servoDAQ1 == HIGH){
    servo1.write(0);
    Serial.println("Gate 1 Open")
    Serial.println("Accepting Cow");
    wait(10000);
  }
  if(servoDAQ2 == HIGH){

  }
  if(dsensor => 0 && RFID == HIGH){
    servo1.write(0);
    servo2.write(a);
    wait(10);
    servo3.write(b);
    wait(10);
    servo4.write(c);
    wait(10);
    servo5.write(d);
    Serial.println("Cow in place");
    if(runi == HIGH){
        Serial.println("Process Starts");
        digitalWrite(pump1, HIGH);
        wait(100);
        digitalWrite(pump2, HIGH);
        wait(100);
        analogWrite(dsensor, A3);
        analogWrite(wsensor, A1);
        if(runi == LOW){
          Serial.println("Process Done");
          wait(100);
          servo2.write(0);
          wait(10);
          servo3.write(0);
          wait(10);
          servo4.write(0);
          wait(10);
          servo5.write(0);
          wait(100);
          servo6.write(0);
          Serial.println("Gate 2 Open");
          if(dsensor => 0 && RFIDi == LOW){
            wait(5000);
            servo6.write(0);
            Serial.println("Gate 2 Close");
          }
          if(dsensor => 0 && RFIDi == HIGH){
            wait(5000);
          }
          if(dsensor => 0 && RFIDi == LOW){
            wait(5000);
            servo6.write(0);
            Serial.println("Gate 2 Close");
          }
        }
      }
    }
  }
}
