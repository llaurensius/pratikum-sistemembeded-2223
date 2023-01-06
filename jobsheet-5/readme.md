
# Jobsheet 5: ADAFRUIT.IO (MQTT) + IFTTT -> SENSOR (DHT11) + LED (ON/OFF) -> SUARA (GOOGLE ASSITANT)

## Anggota Kelompok
- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

## Daftar Isi
  * [Rangkaian](#rangkaian)
  * [Program](#program)
  * [Hasil Percobaan](#hasil-percobaan)
  * [Analisa](#analisa)
  * [Kesimpulan](#kesimpulan)
  
## Rangkaian

<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-5/rangkaian.jpg"   alt="rangkaian" width="300">
<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-5/esp.jpg"   alt="rangkaian" width="300">
<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-5/sensor.jpg"   alt="rangkaian" width="300">

## Program

<details>
  <summary>click to expand</summary>
 
```c 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <DHT.h>

#define WLAN_SSID       "ALPHA 1" 
#define WLAN_PASS       "wologito37"     
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883              
#define AIO_USERNAME    "azpaska"
#define AIO_KEY         "aio_lFJJ47BKS9I94LwxwYjAxnT1N4Q2"
#define DHTPIN D5
#define led1 D0
#define led2 D1
#define led3 D2

DHT dht(DHTPIN, DHT11); 

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/LED-RED");
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED-GREEN");
Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/LED-BLUE");
Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/LED");

float temp,humi;
uint32_t x=0;
void MQTT_connect();
//=========================================================
void setup() {
  Serial.begin(9600);
  delay(10);
  dht.begin();     

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  mqtt.subscribe(&Light1);
  mqtt.subscribe(&Light2);
  mqtt.subscribe(&Light3);
  mqtt.subscribe(&Light);
}
//=============================================
void loop() {  
  MQTT_connect();
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)) {
    Serial.println("DHT11 tidak terbaca... !");
    return;
  }
  else{ 
  // Now we can publish stuff!
    Serial.print("Temperature=");
    Serial.println(temp);
    //Serial.print("...");
    if (! temperature.publish(temp)) {
      Serial.println(F("Publish Temperature Failed"));
      } else {
      Serial.println(F("Publish Temperature OK!"));
    }
    Serial.print("Humidity=");
    Serial.println(humi);
    //Serial.print("...");
      if (! humidity.publish(humi)) {
        Serial.println(F("Publish humidity Failed"));
        } else {
        Serial.println(F("Publish Humidity OK!"));
      }
    delay(5000);  
    }
    
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Light1) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      int Light1_State = atoi((char *)Light1.lastread);
      digitalWrite(led1, Light1_State);

    }
    if (subscription == &Light2) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light2.lastread);
      int Light2_State = atoi((char *)Light2.lastread);
      digitalWrite(led2, Light2_State);
    }
    if (subscription == &Light3) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light3.lastread);
      int Light3_State = atoi((char *)Light3.lastread);
      digitalWrite(led3, Light3_State);
    }
    if (subscription == &Light) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light.lastread);
      int Light_State = atoi((char *)Light.lastread);
      digitalWrite(led1, Light_State);
      digitalWrite(led2, Light_State);
      digitalWrite(led3, Light_State);
    }
  }
}

//===============================================
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
 ```
 </details>

## Hasil Percobaan
 
#### Serial Monitor

<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-5/serial%20monitor.jpg"   alt="serial monitor" width="600">

#### Adafruit.io

<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-5/adafruit.jpg"   alt="hasil" width="600">

#### IFTTT
 
<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-5/ifttt.jpg"   alt="hasil" width="600">
 
#### Demo

 [![Project](http://img.youtube.com/vi/AZ7p4iju2fM/0.jpg)](http://www.youtube.com/watch?v=AZ7p4iju2fM)

## Analisa

Pada percobaan kali ini, digunakan protokok MQTT agar ESP32 dapat berkomunikasi dengan perangkat lain melalui internet. MQTT (Message Queuing Telemetry Transport) protokol merupakan sebuah protokol yang berjalan diatas stack TCP/IP dan dirancang khusus untuk machine to machine yang tidak memiliki alamat khusus. Maksud dari kata tidak memiliki alamat khusus ini seperti halnya sebuah arduino, raspi atau device lain yang tidak memiliki alamat khusus. Sistem kerja MQTT menerapkan Publish dan Subscribe data. Dan pada penerapannya, device akan terhubung pada sebuah Broker dan mempunyai suatu Topic tertentu. Platform MQTT server yang digunakan adalah Adafruit.io. Pada percobaan ini, ESP32 akan mengirimkan data sensor DHT11 (suhu dan kelembaban) ke server MQTT (Adafruit.io) dan akan dicoba untuk melakukan kontrol LED melalui Adafruit.io

Untuk menyambungkan ESP32 dengan Adafruit, ESP32 harus terhubung dengan jaringan WiFi dan server Adafruit

 ```c
// Library yang dibutuhkan
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <DHT.h>

// Informasi WiFi yang akan disambung
#define WLAN_SSID       "ALPHA 1" 
#define WLAN_PASS       "wologito37"    

// Informasi server, username, dan key Adafruit.io
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883              
#define AIO_USERNAME    "azpaska"
#define AIO_KEY         "aio_lFJJ47BKS9I94LwxwYjAxnT1N4Q2"

// Pin Sensor DHT11 dan LED
#define DHTPIN D5
#define led1 D0
#define led2 D1
#define led3 D2
 ```
 
 Karena sistem kerja dari Adafruit.io adalah publish dan subscribe, maka perlu ditambahkan perintah publish dan subscribe pada program
 
  ```c
// Baris program untuk melakukan koneksi ke server Adafruit.io
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Baris program untuk informasi publish (kirim data) ke Adafruit.io
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");

// Baris program untuk informasi subscribe (menerima data) dari Adafruit.io
Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/LED-RED"); // Kontrol LED merah
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED-GREEN"); // Kontrol LED hijau
Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/LED-BLUE"); // Kontrol LED biru
Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/LED"); // Kontrol semua LED
```

Setelah semua informasi didapatkan, maka ESP32 akan mencoba melakukan koneksi dan komunikasi dengan server Adafruit.io

```c
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
```

Saat semua program berjalan dengan baik, maka data ESP32 sudah dapat terlihat pada web Adafruit.io dan dapat melakukan kontrol LED melalui Adafruit.io. Kemudian ditambahkan IFTTT untuk mengontrol ESP32 mwnggunakan voice command yang tersambung dengan Google Assistant. Cara kerja IFTTT adalah mengontrol server Adafruit.io kemudian server akan melanjutkan ke ESP32.

## Kesimpulan

Dari percobaan yang telah dilakukan, didapat kesimpulan sebagai berikut:

- ESP32 dapat berkomunikasi melalui internet melalui suatu protokol. Protokol merupakan peraturan atau prosedur untuk mengirimkan sebuah data pada perangkat elektronik.

- MQTT merukapan suatu protokol yang sangat ringan dan membutuhkan bandwidth yang sangat kecil, sehingga tidak memerlukan jaringan yang cepat. Namun dengan kekurangan protokol ini hanya bisa bertukar data informasi yaitu publish dan subscribe, tidak dapat malakukan operasi create dan delete.

- Salah satu server protokol MQTT yang dapat digunakan adalah Adafruit.io, dengan cara kerja publish (mengirim data ke server) dan subscribe (menerima data dari server).

- ESP32 dapat saling terhubung dengan platform lain melalui internet.

