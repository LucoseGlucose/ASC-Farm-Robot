#include <MFRC522.h>

const int pinRFIDReset = 5;
const int pinRFIDSelect = 53;

extern MFRC522 rfid;

void RFIDBegin();
String RFIDRead();