#include "RFID.h"

MFRC522 rfid = MFRC522(pinRFIDSelect, pinRFIDReset);

void RFIDBegin()
{
    SPI.begin();
    rfid.PCD_Init();
}

String RFIDRead()
{
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    {
        return "";
    }

    String tagID = "";
    for (byte i = 0; i < rfid.uid.size; i++)
    {
        tagID += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
        tagID += String(rfid.uid.uidByte[i], HEX);
    }

    tagID.toUpperCase();

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    return tagID;
}
