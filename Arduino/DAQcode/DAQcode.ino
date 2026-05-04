//Libraries and MACROES
#include <SoftwareSerial.h>

// DAQ Digital Input
int PI0 = 8;
int PI1 = 9;
int PI2 = 10;
int PI3 = 11;

//Arduino OUTPUT
int estop_out = 12;

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
int n = 10;


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
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, LOW);
                analogWrite(A0, 0);
            }
            if (str[1]== '2'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '3'){
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, HIGH);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '4'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, HIGH);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '5'){
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, HIGH);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '6'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, HIGH);
                digitalWrite(PI3, LOW);
            }
            if (str[1] == '7'){
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, HIGH);
                digitalWrite(PI2, HIGH);
                digitalWrite(PI3, LOW);
                analogWrite(A0, 0);
            }
            if (str[1] == '8'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, HIGH);
                digitalWrite(PI2, HIGH);
                digitalWrite(PI3, LOW);
            }
        }
        if (str[0] == 'R'){
            if (str[1] =='1'){
                analogWrite(A0, 36);
            }
            if (str[1] == 'D'){
                analogWrite(A0, 61);
            }
            if (str[1] == '3'){
                analogWrite(A0, 87);
            }
            if( str[1] == 'C'){
                analogWrite(A0, 112);
            }

            /*
            for (int l = 1; l <= 8; l++){
                
                if(str[l] == '0'){
                    analogWrite(A0, 0);
                    delay(n);
                }
                if(str[l] == '1'){
                    analogWrite(A0, 1);
                    delay(n);
                }
                if(str[l] == '2'){
                    analogWrite(A0, 2);
                    delay(n);
                }
                if(str[l] == '3'){
                    analogWrite(A0, 3);
                    delay(n);
                }
                if(str[l] == '4'){
                    analogWrite(A0, 4);
                    delay(n);
                }
                if(str[l] == '5'){
                    analogWrite(A0, 5);
                    delay(n);
                }
                if(str[l] == '6'){
                    analogWrite(A0, 6);
                    delay(n);
                }
                if(str[l] == '7'){
                    analogWrite(A0, 7);
                    delay(n);
                }
                if(str[l] == '8'){
                    analogWrite(A0, 8);
                    delay(n);
                }
                if(str[l] == '9'){
                    analogWrite(A0, 9);
                    delay(n);
                }
                if(str[l] == 'A'){
                    analogWrite(A0, 10);
                    delay(n);
                }
                if(str[l] == 'B'){
                    analogWrite(A0, 11);
                    delay(n);
                }
                if(str[l] == 'C'){
                    analogWrite(A0, 12);
                    delay(n);
                }
                if(str[l] == 'D'){
                    analogWrite(A0, 13);
                    delay(n);
                }
                if(str[l] == 'E'){
                    analogWrite(A0, 14);
                    delay(n);
                }
                if(str[l] == 'F'){
                    analogWrite(A0, 15);
                    delay(n);
                }
            }
            */
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
        if (str[0] == 'G'){
            if (str[1] == 'O'){
                digitalWrite(PI0, LOW);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, HIGH);
            }
            if (str[0] == 'C'){
                digitalWrite(PI0, HIGH);
                digitalWrite(PI1, LOW);
                digitalWrite(PI2, LOW);
                digitalWrite(PI3, HIGH);
            }
        }
        
    }
    if (Serial.available()){
        serialFromPi.print(Serial.readString());
        if (estop == HIGH){
            digitalWrite(estop_out, LOW);
        }
        if (estop == LOW){
            digitalWrite(estop_out, HIGH);
        }
        if (home == HIGH){
            Serial.println("HHOME");
        }
    }
}