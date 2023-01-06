# Jobsheet 1.1
JARINGAN SENSOR NIRKABEL MENGGUNAKAN ESP-NOW



## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

# Analisa

Dalam praktikum ini, digunakan 2 buah ESP32 agar dapat saling berkomuniasi secara dua arah.

### A. Membaca Sensor DHT11 

```c
#include "DHT.h" // Library yang dibutuhkan untuk run program
#define DHTPIN 4 // Pin digital yang terhubung dengan pin data sensor
#define DHTTYPE DHT11 // Tipe sensor DHT yang digunakan

DHT dht(DHTPIN, DHTTYPE); // inisialisasi sensor DHT
// inisialisasi setup koneksi ESP dengan laptop
void setup() {
 Serial.begin(115200);
 Serial.println(F("DHT11 Embedded System Test!"));
 dht.begin();
}

void loop() {
 // memberi delay pada tiap pengukuran selama 2 detik
 delay(2000);
 
 // Membaca temperatur dan kelembaban membutuhkan waktu setidaknya 250ms
 // Pembacaan sensor dapat melebihi 2 detik dikarenakan sensor lambat
 float h = dht.readHumidity();
 // Membaca temperature sebagai Celsius (bawaan)
 float t = dht.readTemperature();
 
 // Membaca temperatur sebagai Fahrenheit (isFahrenheit = true)
 float f = dht.readTemperature(true);
 
 // Mengecek apakah terjadi kegagalan pembacaan sensor dan melakukan pembacaan ulang.
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 
 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);
 Serial.print(F("Humidity: "));
 Serial.print(h);
 Serial.print(F("% Temperature: "));
 Serial.print(t);
 Serial.print(F("°C "));
 Serial.print(f);
 Serial.print(F("°F Heat index: "));
 Serial.print(hic);
 Serial.print(F("°C "));
 Serial.print(hif);
 Serial.println(F("°F"));
}
```
### B. Two-Way Communication DHT11

```c
//Library yang dibutuhkan
#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE); // inisialisasi sensor DHT
// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0xBB, 0x3A, 0x94};

// Define variables
float temperature;
float humidity;

// Define variables to store incoming readings
float incomingTemp;
float incomingHum;

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
 float temp;
 float hum;
} struct_message;

// Create a struct_message sensors reading
struct_message DHTReadings;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;
esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
 Serial.print("\r\nLast Packet Send Status:\t");
 Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
 if (status ==0){
 success = "Delivery Success :)";
 }
 else{
 success = "Delivery Fail :(";
 }
}
// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
 memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
 Serial.print("Bytes received: ");
 Serial.println(len);
 incomingTemp = incomingReadings.temp;
 incomingHum = incomingReadings.hum;
}
void setup() {
 // Init Serial Monitor
 Serial.begin(115200);
 
 // Init DHT
 dht.begin();
 
 // Set device as a Wi-Fi Station
 WiFi.mode(WIFI_STA);
 
 // Init ESP-NOW
 if (esp_now_init() != ESP_OK) {
 Serial.println("Error initializing ESP-NOW");
 return;
 }
 
 // Once ESPNow is successfully Init, we will register for Send CB to
 // get the status of Trasnmitted packet
 esp_now_register_send_cb(OnDataSent);

 // Register peer
 memcpy(peerInfo.peer_addr, broadcastAddress, 6);
 peerInfo.channel = 0;
 peerInfo.encrypt = false;

 // Add peer
 if (esp_now_add_peer(&peerInfo) != ESP_OK){
 Serial.println("Failed to add peer");
 return;
 }
 
 // Register for a callback function that will be called when data is received
 esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
 delay(2000);
 getReadings();
 // Set values to send
 DHTReadings.temp = temperature;
 DHTReadings.hum = humidity;
 
 // Send message via ESP-NOW
 esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &DHTReadings,
sizeof(DHTReadings));

 if (result == ESP_OK) {
 Serial.println("Sent with success");
 }
 else {
 Serial.println("Error sending the data");
 }

 delay(1000);
}
void getReadings(){
 float t = dht.readTemperature();
 float h = dht.readHumidity();
 float f = dht.readTemperature(true);
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 Serial.print(F("Humidity: "));
 Serial.print(h);
 Serial.print(F("% Temperature: "));
 Serial.print(t);
 Serial.print(F("°C "));
}
```


# Kesimpulan

Dalam praktikum yang menggunakan protokol ESP-NOW memberikan kesimpulan bahwa ESP dapat saling berkomunasi dengan metode dua arah atau mengirim dan menerima data sekaligus.

Dalam praktikum ini data berhasil dikirimkan dari satu ESP A ke ESP B, begitu juga ESP A dapat menerima data dari ESP B. Hal yang serupa juga terjadi pada ESP B, yaitu mengirim data ke ESP A dan menerima data dari ESP A

# Dokumentasi
## DHT11 Read
![500000](https://user-images.githubusercontent.com/118155742/210127901-444d1674-53e9-433c-8b2d-fafd67f2d557.jpg)

Dokumentasi Video

 [![Project](http://img.youtube.com/vi/u8l7PD0T5oc/0.jpg)](http://www.youtube.com/watch?v=u8l7PD0T5oc)


### Tx & Rx DHT11 Data
![test](https://user-images.githubusercontent.com/118155742/210127905-9a06ed43-51f1-4c68-a107-5ef8157ab890.jpg)

### Dokumentasi Video

 [![Project](http://img.youtube.com/vi/mjIHEiJML1Q/0.jpg)](http://www.youtube.com/watch?v=mjIHEiJML1Q)
