#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN    21  // ESP32 pin GIO21 
#define RST_PIN   22 // ESP32 pin GIO22
const int ledPin1 = 32;
const int ledPin2 = 12;
static const int servoPin = 4;
Servo servo1;

MFRC522 rfid(SS_PIN, RST_PIN);
byte keyTagUID[4] = {0x53, 0xB5, 0xE0, 0x16}; //53 B5 E0 16
void setup() {
Serial.begin(9600);
pinMode (ledPin1, OUTPUT);
pinMode (ledPin2, OUTPUT);
servo1.attach(servoPin);
SPI.begin(); // init SPI bus
rfid.PCD_Init(); // init MFRC522
Serial.println("Tap RFID/NFC Tag on reader"); 
delay(1000);

}
void loop() {
if (rfid.PICC_IsNewCardPresent()) { // new tag is available
if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak); 
if (rfid.uid.uidByte[0] == keyTagUID[0] &&
rfid.uid.uidByte[1] == keyTagUID[1] &&
rfid.uid.uidByte[2] == keyTagUID[2] &&
rfid.uid.uidByte[3] == keyTagUID[3] ) {
  Serial.println(); 
Serial.println("Access is granted");
Serial.println("SERVO BERGERAK");
digitalWrite(ledPin2, HIGH);
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        delay(5);
    }
delay(5000);
digitalWrite(ledPin2, LOW);
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        delay(20);
    }
    
} 
else 
{
  Serial.println();
Serial.print("Access denied for user with UID:");
for (int i = 0; i < rfid.uid.size; i++) {
  Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "); 
Serial.print(rfid.uid.uidByte[i], HEX);
}
digitalWrite(ledPin1, HIGH);
delay(3000); 
digitalWrite(ledPin1, LOW);

}
rfid.PICC_HaltA(); // halt PICC
rfid.PCD_StopCrypto1(); // stop encryption on PCD
}
}
}
