#include <SoftwareSerial.h>
// DAQ Digital Input
int PI0 = 8;
int PI1 = 9;
int PI2 = 10;
int PI3 = 11;


// DAQ Digital Outputs
int estop = 4;
int home = 5;

// DAQ Analog Inputs
float wsensor = 0;
float dsensor = 0;

//variables
String str;
String str_x;
String str_y;


SoftwareSerial serialFromPi = SoftwareSerial(3, 2);

void setup(){
    serialFromPi.begin(19200);
    Serial.begin(19200);

    //Initalize DAQ Digital Inputs
    pinMode(PI0, OUTPUT);
    pinMode(PI1, OUTPUT);
    pinMode(PI2, OUTPUT);
    pinMode(PI3, OUTPUT);

    //Initalize DAQ Outputs
    pinMode(estop, INPUT);
    pinMode(home, INPUT);
}

void loop(){
    if (serialFromPi.available())
    {
        Serial.print(serialFromPi.readStringUntil(';'));
        str = Serial.readString();
        if(str[0] = 'U'){
            if (str[1] == '1'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, LOW);
            }
            if (str[1]== '2'){
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, HIGH);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '3'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, HIGH);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '4'){
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, HIGH);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '5'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, HIGH);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '6'){
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, HIGH);
                digitalWrite(PI2, HIGH);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '7'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, HIGH);
                digitalWrite(PI2, HIGH);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '8'){
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, HIGH);
            }
        }
        if (str[0] == 'R'){
            String R = str.substring(1);
            int IDnum = R.toInt();
            analogWrite(A0, IDnum);
        }
        if (str[0] == 'F'){
            String F = str.substring(1);
            int flow = F.toInt();
            analogWrite(A1, flow);
        }
        if (str[0] == 'D'){
            String D = str.substring(1);
            int z = D.toInt();
            analogWrite(A2, z);
        }
        if (str[0] == 'T'){
            String T = str.substring(1);
            int time = T.toInt();
            analogWrite(A3, time);
        }
        if (str[0] == 'C'){
            for (int i = 0; i < str.length(); i++) {
                if (str.substring(i, i+1) == ",") {
                    str_x = str.substring(1, i);
                    str_y = str.substring(i+1);
                    break;
                }
            }
            int x = str_x.toInt();
            int y = str_y.toInt();
            analogWrite(A4, x);
            analogWrite(A5, y);
        }
    }

    if (Serial.available()){
        serialFromPi.print(Serial.readString());

    }
}