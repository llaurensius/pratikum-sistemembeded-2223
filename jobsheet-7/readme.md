
# Jobsheet 7
ESP-NOW (MANY TO ONE) + CAYENNE + SENSOR (DHT11)


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

## Skematik
![image](https://user-images.githubusercontent.com/118155742/210129990-1018d897-059b-447a-8e66-28f8216831c3.png)


## Analisa
Dalam pratikum ini memakai protokol ESP-NOW berjumlah 3 buah ESP32 yang terbagiatas 2 buah ESP32 sebagai Sender dengan terhubung sensor DHT11 dan 1 buah ESP32 sebagai Receive/Koordinator yang akan mengirimkan nilai sensor dari 2 buah ESP32 tadi ke Cayenne.

### Sender/Transmitter

```c
//Library yang dibutuhkan
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include "DHT.h"

//Mendefinisikan DHT11 di pin GPIO 4 dan jenis DHT yang digunakan
#define DHTPIN 4
#define DHTTYPE DHT11

//Mac Address yang akan dituju untuk menerima data
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0x9C, 0x13, 0x8C};

//Board ID ESP32 - digunakan sebagai identifikasi ESP yang terhubung ke koordinator
const int espNumber = 2;

//Struktur data yang akan dikirimkan, struktur data harus sama dengan receiver
typedef struct struct_message {
  int id;
  float temp;
  float hum;
} struct_message;

//membuat struktur data dengan nama myData
struct_message myData;

//Membuat interface peer
esp_now_peer_info_t peerInfo;

//Mengirim notifikasi apabila data berhasil dikirimkan
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Variable untuk membaca temperature dan humidity
float temperature;
float humidity;

WiFiClient  client;

//Mengisisiasi pin GPIO dan tipe DHT11 yang tersambung
DHT dht(DHTPIN, DHTTYPE);

//Memasukan nama SSID yang sama-sama tersambung
constexpr char WIFI_SSID[] = "k";

//Memindai channel wifi untuk ditumpangi dalam pengiriman data
int32_t getWiFiChannel(const char *ssid) {
  if (int32_t n = WiFi.scanNetworks()) {
    for (uint8_t i = 0; i < n; i++) {
      if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
        return WiFi.channel(i);
      }
    }
  }
  return 0;
}
void setup() {
  Serial.begin(115200); //Memulai serial dengan 115200 baud rate
  dht.begin(); // Memulai fungsi DHT
  WiFi.mode(WIFI_STA); //Membuat ESP32 sebagai station
  
  //Mendapatkan channel wifi
  int32_t channel = getWiFiChannel(WIFI_SSID); 

  WiFi.printDiag(Serial); // Uncomment to verify channel number before
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  WiFi.printDiag(Serial);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  //Mengirimkan data ke ESP32 yang ditunjuk sebagai koordinator sekaligus mengirimkan feedback apabila paket diterima koordinator
  esp_now_register_send_cb(OnDataSent); 

  //Regristasi peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6); 
  //peerInfo.channel = 0;
  peerInfo.encrypt = false;

  //Menambahkan peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {

//Membaca nilai sensor temperature dan humidity dari DHT11 dan memverifikasi nilai data, apabila nilai sensor terbaca maka disimpan di variabel humidity & temperature
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
 //Menampilkan pembacaan nilai sensor
  Serial.print("Temperature (ºC): ");
  Serial.print(temperature);
  Serial.print(" Humidity (%): ");
  Serial.println(humidity);

//Mengirimkan data nilai sensor ke ESP32 Koordinator
  myData.id = espNumber;
  myData.temp = temperature;
  myData.hum = humidity;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

//Memberitahukan bahwa pesan sukses/gagal dikirim
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(1000);
}
```

## Receiver/Koordinator
```c
//library yang dibutuhkan
#include <esp_now.h>
#include <WiFi.h>
#include <CayenneMQTTESP32.h>
#define CAYENNE_PRINT Serial

//Struktur data yang dibutuhkan untuk menerima data dari ESP32 lain
typedef struct struct_message {
  int id;
  float temp;
  float hum;
} struct_message;

//Membuat struktur data myData, board1, board2, board3
struct_message myData;
struct_message board1;
struct_message board2;
struct_message board3;
struct_message boardsStruct[3] = {board1, board2, board3};

//Autentikasi untuk tersambung ke WiFi dan Cayenne
const char* ssid = "k";   // your network SSID (name)
const char* password = "123456779";   // your network password
const char* username = "fa9de470-7f7b-11ed-b193-d9789b2af62b";
const char* mqtt_password = "3b449543f2b1413ddffea61e5828a05ff09f07d6";
const char* cliend_id = "40ce4d40-87f6-11ed-8d53-d7cd1025126a";
float temperature[3];
float humidity[3];

//Memberitahukan apabila data berhasil diterima akan tampil di serial monitor
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4],
           mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  boardsStruct[myData.id - 1].temp = myData.temp;
  boardsStruct[myData.id - 1].hum = myData.hum;
  Serial.printf("Board: %d \n", myData.id);
  Serial.printf("Temperature: %.2f \n", boardsStruct[myData.id - 1].temp);
  Serial.printf("Humidity: %.2f \n", boardsStruct[myData.id - 1].hum);
  Serial.println();
  temperature[myData.id - 1] = boardsStruct[myData.id - 1].temp;
  humidity[myData.id - 1] = boardsStruct[myData.id - 1].hum;
}

void setup() {
  Serial.begin(115200);//Inisiasli serial dengan 115200 baud rate
  WiFi.mode(WIFI_STA);//Inisiasi ESP32 menjadi station
  //Inisiasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //Mendapatkan informasi dari ESP32 yang mengirimkan data ke Koordinator
  esp_now_register_recv_cb(OnDataRecv);
  Cayenne.begin(username, mqtt_password, cliend_id, ssid, password);
}

void loop() {
  Cayenne.loop(); //Mebuat fungsi Cayenne berjalan berulang-ulang untuk mengirimkan data
  delay(1000);
}
//Mengirimkan data ke Cayenne yang diterima oleh ESP32 koordinator, terdapat 2 ESP32 yang menjadi transmitter
CAYENNE_OUT_DEFAULT()
{
  Cayenne.virtualWrite(1, temperature[0], "temperature", "Celcius");
  Cayenne.virtualWrite(2, humidity[0], "humidity", "%");
  Cayenne.virtualWrite(3, temperature[1], "temperature", "Celcius");
  Cayenne.virtualWrite(4, humidity[1], "humidity", "%");
  Cayenne.virtualWrite(5, temperature[2], "temperature", "Celcius");
  Cayenne.virtualWrite(6, humidity[2], "humidity", "%");
}
```

# Kesimpulan
Dalam pratikum ini disimpulkan bahwa pemrogaman untuk IoT dapat dikembangkan lebih lanjut, dengan protokol komunikasi antar ESP32 melalui ESP-NOW dan dapat dikembangkan untuk saling bertukar data dengan memanfaatkan nilai dari sensor DHT11. Kedepannya dapat dikembangkan untuk mengirimkan data sensor-sensor lainnya.

Nilai dari sensor DHT11 dibaca oleh dashboard Cayenne yang dikirimkan oleh ESP32 Koordinator.

# Dokumentasi

https://user-images.githubusercontent.com/118155742/210124601-eee6d110-c30e-48f0-9464-878043d8c443.mp4

