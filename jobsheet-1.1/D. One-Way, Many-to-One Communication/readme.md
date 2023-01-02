# Jobsheet 1.1
JARINGAN SENSOR NIRKABEL MENGGUNAKAN ESP-NOW

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

# Analisa
Dalam pratikum ini menggunakan 4 buah ESP32 yang terdiri dari 3 sebagai sender/transmitter dan 1 sebagai receiver/koordinator

## Transmitter
```c
//Library yang digunakan
#include <esp_now.h>
#include <WiFi.h>

//MAC Address yang menjadi tujuan untuk protokol ini
// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0x24, 0x6F, 0x28, 0x02, 0xC3, 0x1C}; //24:6F:28:02:C3:1C
uint8_t broadcastAddress2[] = {0x24, 0x0A, 0xC4, 0XC6, 0x06, 0x54}; //24:0A:C4:C6:06:54
uint8_t broadcastAddress3[] = {0x8C, 0xCE, 0x4E, 0xC8, 0x29, 0x1B}; //8C:CE:4E:C8:29:1B

//membuat struktur data untuk mengirimkan pesan
typedef struct test_struct {
  int x;
  int y;
} test_struct;

//membuat variabel struktur data bernama test
test_struct test;

//membuat variabel tipe esp_now_peer_info_t untuk menampung informasi terkait peer
esp_now_peer_info_t peerInfo;

//memberikan respon ketika data terkirim atau tidak terkirim di ESP koordinator
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200); //Inisialisasi serial monitor untuk debugging
 
  WiFi.mode(WIFI_STA); //Inisialisasi ESP32 sebagai WiFi Station
 
 //Inisialisasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  //Setelah ESP-NOW berhasil diinisialisasi, akan register ke fungsi respon OnDataSet() yang telah dibuat
  esp_now_register_send_cb(OnDataSent);
   
  // register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // register peer pertama
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // register peer kedua
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  /// register peer ketiga
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
//Mengirim data ke board yang berbeda-beda dengan mengirimkan struktur data yang berbeda-beda
  test_struct test1;
  test_struct test2;
  test_struct test3;
  
  test1.x = random(0,20);
  test1.y = random(0,20);

  test2.x = random(0,20);
  test2.y = random(0,20);

  test2.x = random(0,20);
  test2.y = random(0,20);
 
 //Mengirimkan data ke receiver sekaligus mengecek apakah data berhasil dikirim
  esp_err_t result1 = esp_now_send(broadcastAddress1, (uint8_t *) &test1, sizeof(test_struct));
   
  if (result1 == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  esp_err_t result2 = esp_now_send(
  broadcastAddress2, 
  (uint8_t *) &test2,
  sizeof(test_struct));

if (result2 == ESP_OK) {
  Serial.println("Sent with success");
}
else {
  Serial.println("Error sending the data");
}

  esp_err_t result3 = esp_now_send(
  broadcastAddress3, 
  (uint8_t *) &test3,
  sizeof(test_struct));

if (result3 == ESP_OK) {
  Serial.println("Sent with success");
}
else {
  Serial.println("Error sending the data");
}
  delay(2000);

  
}
```

## Receiver
```c
//Library yang digunakan
#include <esp_now.h> 
#include <WiFi.h>

//Struktur data yang akan dikirimkan
typedef struct test_struct {
int x; 
int y;
} test_struct;

//membuat struktur data menjadi variabel test
test_struct test;

//fungsi untuk memberikan respon apabila data berhasil diterima
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { 
memcpy(&test, incomingData, sizeof(test));
Serial.print("Bytes received: ");
Serial.println(len);
Serial.print("x: ");
Serial.println(test.x);
Serial.print("y: ");
Serial.println(test.y);
Serial.println(); 
}
void setup() {
//Inisialisasi Serial monitor untuk debugging 
Serial.begin(115200);

//Inisialisasi ESP sebagai WiFi Station
WiFi.mode(WIFI_STA);

//Inisialisasi ESP-NOW
if (esp_now_init() != ESP_OK) {
  Serial.println("Error initializing ESP-NOW"); 
return;
}
//register ke fungsi callback OnDataRecv() untuk memberitahukan bahwa data telah diterima
esp_now_register_recv_cb(OnDataRecv); 
}
void loop() { 
}
```
# Kesimpulan
Dalam pratikum yang memanfaatkan protokol ESP-NOW untuk mengirimkan data dari satu ESP ke beberapa ESP memberikan kesimpulan bahwa ESP dapat saling berkomunikasi ke beberapa board untuk mengirimkan data.

Dalam pratikum kali ini data berhasil dikirimkan dari satu ESP dan diterima oleh tiga ESP, jika salah satu penerima ESP mati maka data tidak terkirim dari ESP pengirim.

# Dokumentasi


