# Jobsheet 1.1
JARINGAN SENSOR NIRKABEL MENGGUNAKAN ESP-NOW

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

# Analisa
Dalam koding ini terdapat 2 buah ESP32 yang berfungsi sebagai receiver dan transmitter.

## Transmitter
```c
//Library yang dibutuhkan
#include <esp_now.h>
#include <WiFi.h>

//MAC Address tujuan yang akan dikirim, terdapat beberapa MAC Address karena pratikum ini mencoba untuk mengirim di beberapa Board
// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0x24, 0x6F, 0x28, 0x02, 0xC3, 0x1C}; //24:6F:28:02:C3:1C
uint8_t broadcastAddress2[] = {0x24, 0x0A, 0xC4, 0XC6, 0x06, 0x54}; //24:0A:C4:C6:06:54
uint8_t broadcastAddress3[] = {0x8C, 0xCE, 0x4E, 0xC8, 0x29, 0x1B}; //8C:CE:4E:C8:29:1B

//Membuat struktur data yang akan dikirimkan, data dalam struktur ini ada 2 variabel dan dapat ditambah sesuai dengan keinginan.
typedef struct test_struct {
  int x;
  int y;
} test_struct;

//Membuat struktur data dengan nama myData
test_struct myData;

//Membuat variabel dengan tipe esp_now_peer_info_t untuk mengumpulkan informasi tentang peer
esp_now_peer_info_t peerInfo;

//Berfungsi ketika eksekusi data yang dikirimkan. Dalam fungsi ini ketika pesan berhahsil terkirim maka akan tampil jawaban di serial monitor pengirim.
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
  Serial.begin(115200); //Inisialisasi serial monitor untuk keperluan debugging
 
  WiFi.mode(WIFI_STA); //Inisialisasi perangkat ESP32 sebagai WiFi Station
 
  //Inisialisasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  //Ketika inisialisasi ESP-Now sukses maka akan diarahkan ke fungsi OnDataSent yang telah dibuat diatas.
  esp_now_register_send_cb(OnDataSent);
   
  //Menambahkan peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  //Regrister perangkat EPS lain yang pertama 
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //Regrister perangkat EPS lain yang kedua
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //Regrister perangkat EPS lain yang ketiga
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  //Data yang akan dikirimkan berupa data random mulai dari 0-20
  test.x = random(0,20);
  test.y = random(0,20);
 
  //Mengirimkan data ke beberapa board
  esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));
   
  //Fungsi untuk mengecek data di atas apakah sudah terkirim
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000); //Jeda loop selama 2 detik
}
```

## Receiver
```c
//Menambahkan library yang digunakan
#include <esp_now.h> 
#include <WiFi.h>

//Struktur untuk menerima data, harus sama dengan transmitter
typedef struct test_struct {
int x; 
int y;
} test_struct;

//Membuat struktur data dengan nama myData 
test_struct myData;

//Membuat fungsi callback yang memberitahu data yang diterima
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { 
memcpy(&myData, incomingData, sizeof(myData));
Serial.print("Bytes received: ");
Serial.println(len);
Serial.print("x: ");
Serial.println(myData.x);
Serial.print("y: ");
Serial.println(myData.y);
Serial.println(); 
}
void setup() {
//Inisialisasi serial monitor untuk debugging
Serial.begin(115200);

//Membuat ESP32 sebagai WiFi Station
WiFi.mode(WIFI_STA);

//Inisialisasi ESP-NOW
if (esp_now_init() != ESP_OK) {
  Serial.println("Error initializing ESP-NOW"); 
return;
}

//Ketika ESP-Now berhasil maka akan menerima data dari transmitter
esp_now_register_recv_cb(OnDataRecv); 
}
void loop() { 
}
```
# Kesimpulan
Dalam pratikum ini ESP32 berkomunikasi melalui protokol ESP-NOW dengan 3 board  ESP32 mengirim di 1 ESP32. 

Perangkat ESP akan berkomunikasi melalui WiFi yang saling terhubung satu sama lain dengan mengirimkan data random berupa angka random.

Percobaan berhasil dengan mengirim data dari 3 ESP ke 1 ESP sesuai protokol ESP-NOW dan memmbuktikan bahwa EPS32 dapat saling berkomunikasi secara langsung


# Dokumentasi

