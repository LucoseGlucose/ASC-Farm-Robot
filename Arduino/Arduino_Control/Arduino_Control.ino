#include <SPI.h>
#include <MFRC522.h>

//--- Pin Definitions ---
//hardware interrupts can only be on digital pins 2 and 3.
const byte ESTOP_PIN = 2; 
const byte RESET_BTN_PIN = 4;   //Standard digital pin for the Reset Button

#define RST_PIN 9          
#define SS_PIN 10         
MFRC522 rfid(SS_PIN, RST_PIN);

//--- State Definitions ---
enum SystemState {
  STATE_INIT,
  IDLE,
  READ_RFID,
  CONTROL_ARM,
  ESTOP
};

//This variable can change outside the main flow of the program
volatile SystemState currentState = STATE_INIT;
volatile bool estopTriggered = false;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  //Configure the E-stop and Reset pins
  //E-stop button should connect Pin 2 to GND when pressed.
  pinMode(ESTOP_PIN, INPUT_PULLUP);
  pinMode(RESET_BTN_PIN, INPUT_PULLUP);
 
  //Interrupt will trigger when the voltage drops from HIGH to LOW (button pressed).
  attachInterrupt(digitalPinToInterrupt(ESTOP_PIN), EStop, FALLING);
}

void loop() {
  //1. Absolute Priority: Check the interrupt flag
  if (estopTriggered && currentState != ESTOP) {
    currentState = ESTOP;
  }

  //2. State Machine Logic
  switch (currentState) {
    
    case STATE_INIT:
      //Perform startup calibrations here
      Serial.println("System Initialized. Entering IDLE.");
      currentState = IDLE;
      break;

    case IDLE:
      //Wait here until command is sent to change states
      if (Serial.available() > 0) {
        char cmd = Serial.read();
        if (cmd == 'R') currentState = READ_RFID;
        if (cmd == 'A') currentState = CONTROL_ARM;
      }
      break;

    case READ_RFID:
      //Execute RFID
      readCowTag();
      
      //Once done, return to IDLE or wait for the Pi's next instruction
      currentState = IDLE; 
      break;

    case CONTROL_ARM:
      //Execute robotic arm logic (Still needs to be coded)
      //Note: Avoid blocking code like long delay() here, or break tasks into smaller steps.
      
      //Return to IDLE when movement is complete
      currentState = IDLE;
      break;

    case ESTOP:
      //Code is trapped here. All motors and pump will be shut off (still need to be coded)
      Serial.println("CRITICAL: E-STOP TRIGGERED. SYSTEM HALTED.");
      //Check for the reset button.
      if (digitalRead(RESET_BTN_PIN) == LOW) {
        
        //Clear the volatile interrupt flag
        estopTriggered = false;
        
        //Route back to INIT to recalibrate machine
        currentState = STATE_INIT;
        Serial.println("E-STOP CLEARED. Rebooting system...");
        
        //Brief delay to prevent the button press from triggering multiple state jumps
        delay(500); 
      }
      break;
  }
}

//--- Functions ---
void EStop() {
  estopTriggered = true;
}

void readCowTag() {
  /*
  * RFID-RC522 to Elegoo Uno R3 Wiring Map
  * ---------------------------------------
  * CRITICAL WARNING: The RFID-RC522 module operates strictly on 3.3V. 
  * Connecting the 3.3V pin to the Arduino's 5V pin will permanently damage the reader.
  * RFID-RC522 Pin | Elegoo Uno R3 Pin | Function
  * ---------------|-------------------|---------------------------------------------
  * 3.3V           | 3.3V              | Power Supply
  * RST            | Pin 9             | Reset
  * GND            | GND               | Ground
  * IRQ            | Not Connected     | Interrupt Request (Not required for polling)
  * MISO           | Pin 12            | Master In Slave Out (Data to Arduino)
  * MOSI           | Pin 11            | Master Out Slave In (Data to RFID)
  * SCK            | Pin 13            | Serial Clock
  * SDA (SS)       | Pin 10            | Slave Select
  */
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  String tagID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tagID += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    tagID += String(rfid.uid.uidByte[i], HEX);
  }
  tagID.toUpperCase();
  Serial.println(tagID);
  
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}