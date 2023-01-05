# Analisa

### Membaca RFID
```c
//Library yang dibutuhkan
#include <SPI.h>
#include <MFRC522.h>

//Inisialisasi pin untuk RFID Reader
#define SS_PIN    21  // ESP32 pin GIO21 
#define RST_PIN   22 // ESP32 pin GIO22

//Inisialisasi RFID module
MFRC522 rfid(SS_PIN, RST_PIN);

//MAC Address yang ada di kartu
byte keyTagUID[7] = {0x05, 0x83, 0x4B, 0x7D, 0x30, 0xD1, 0x00}; //05 83 4B 7D 30 D1 00
void setup() {
//Inisialisasi serial monitor untuk debugging
Serial.begin(9600);

//Inisialisasi SPI bus
SPI.begin();

//Inisialisasi MFRC522
rfid.PCD_Init();

//Print tulisan ketika ESP pertama kali dijalankan
Serial.println("Tap RFID/NFC Tag on reader"); 
}
void loop() {


if (rfid.PICC_IsNewCardPresent()) { // Kartu baru ditambahkan
if (rfid.PICC_ReadCardSerial()) { // NUID ID telah terbaca
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak); //Verifikasi pencocokan kartu dengan MAC yang telah diatur 
if (rfid.uid.uidByte[0] == keyTagUID[0] &&
rfid.uid.uidByte[1] == keyTagUID[1] &&
rfid.uid.uidByte[2] == keyTagUID[2] &&
rfid.uid.uidByte[3] == keyTagUID[3] &&
rfid.uid.uidByte[4] == keyTagUID[4] &&
rfid.uid.uidByte[5] == keyTagUID[5] &&
rfid.uid.uidByte[6] == keyTagUID[6] ) { 
Serial.println("Access is granted"); //Ketika kartu yang didaftarkan sesuai maka akan memberikan jawaban 
} 
else 
{
Serial.print("Access denied for user with UID:"); //Ketika kartu yang dibaca tidak sesuai dengan yang didaftarkan maka akan ditolak

//Print MAC Address kartu
for (int i = 0; i < rfid.uid.size; i++) {
  Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "); 
Serial.print(rfid.uid.uidByte[i], HEX);
}
Serial.println(); 
}
rfid.PICC_HaltA(); // halt PICC
rfid.PCD_StopCrypto1(); // stop encryption on PCD
}
}
}
```

### Memberikan akses untuk RFID 
```c
//Library yang digunakan
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//Inisialisasi pin untuk RFID Reader
#define SS_PIN    21  // ESP32 pin GIO21 
#define RST_PIN   22 // ESP32 pin GIO22

//Inisialisasi pin untuk LED & Servo
const int ledPin1 = 32;
const int ledPin2 = 12;
static const int servoPin = 4;

//Memberi nama Servo
Servo servo1;

//Kartu yang didaftarkan
MFRC522 rfid(SS_PIN, RST_PIN);
byte keyTagUID[4] = {0x53, 0xB5, 0xE0, 0x16}; //53 B5 E0 16

void setup() {
//Inisialisasi serial monitor untuk debugging
Serial.begin(9600);

//Mengatur LED sebagai output
pinMode (ledPin1, OUTPUT);
pinMode (ledPin2, OUTPUT);

//Inisialisasi Servo
servo1.attach(servoPin);

//Inisialisasi RFID Module
SPI.begin(); // init SPI bus
rfid.PCD_Init(); // init MFRC522
Serial.println("Tap RFID/NFC Tag on reader"); 
delay(1000);

}
void loop() {

if (rfid.PICC_IsNewCardPresent()) { //Tag baru ditambahkan
if (rfid.PICC_ReadCardSerial()) { //Kartu baru saja dibaca

//Verifikasi kartu apakah sama dengan yang didaftarkan
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak); 
if (rfid.uid.uidByte[0] == keyTagUID[0] &&
rfid.uid.uidByte[1] == keyTagUID[1] &&
rfid.uid.uidByte[2] == keyTagUID[2] &&
rfid.uid.uidByte[3] == keyTagUID[3] ) {
  Serial.println(); 
Serial.println("Access is granted"); //Akses diberikan ketika kartu yang dibaca sama dengan yang didaftarkan
Serial.println("SERVO BERGERAK"); //Print untuk memberitahukan bahwa servo bergerak
digitalWrite(ledPin2, HIGH); //LED Hidup karena kartu yang dibaca sesuai

//Servo bergerak karena kartu yang dibaca sesuai
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        delay(5);
    }
delay(5000);
digitalWrite(ledPin2, LOW); //LED dimatikan

//Servo bergerak kembali ke posisi awal
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        delay(20);
    }
    
} 
else //Ketika kartu yang dibaca tidak sesuai maka tidak ada pergerakan 
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
```

# Kesimpulan
Pratikum ini memberikan kesimpulan dalam pembacaan sensor dapat menjadi suatu input bagi keluaran perangkat lainnya, seperti dalam RFID yang membaca kartu yang benar maka akan membuat LED dan Servo bergerak sesuai dengan yang diperintahkan.

Dalam pratik sesungguhnya, RFID dapat dikembangkan sebagai trigger bagi keluaran lain seperti dalam ini sensor RFID bisa menjadi trigger bagi servo dan LED


# Dokumentasi


https://user-images.githubusercontent.com/118155742/210376398-4ca775cf-230d-4e57-b49d-2fe7a8d9ce94.mp4






