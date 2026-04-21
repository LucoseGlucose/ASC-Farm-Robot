/*
 * RFID-RC522 to Elegoo Uno R3 Wiring Map
 * ---------------------------------------
 * CRITICAL WARNING: The RFID-RC522 module operates strictly on 3.3V. 
 * Connecting the 3.3V pin to the Arduino's 5V pin will permanently damage the reader.
 * * RFID-RC522 Pin | Elegoo Uno R3 Pin | Function
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

//Program to read RFID tag and send it back over Serial communication
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10         

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Initialize serial communication with the Pi
  SPI.begin();        // Initialize SPI bus
  rfid.PCD_Init();    // Initialize MFRC522 module
}

void loop() {
  // put your main code here, to run repeatedly:
  // Check if a new card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Verify if the UID has been read
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Create a string to hold the UID
  String tagID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    // Format the UID into a readable hex string
    tagID += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    tagID += String(rfid.uid.uidByte[i], HEX);
  }
  
  // Send the formatted tag ID to the Raspberry Pi followed by a newline
  tagID.toUpperCase();
  Serial.println(tagID);

  // Halt the PICC before reading again to prevent spamming the serial port
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
