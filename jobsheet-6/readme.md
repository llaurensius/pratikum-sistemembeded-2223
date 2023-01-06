
# Jobsheet 6: THINGSPEAK (HTTP/REST) + SENSOR (DHT11)


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

<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-6/rangkaian.jpg"   alt="rangkaian" width="300">

## Program

<details>
  <summary>click to expand</summary>
 
```c
#include <DHT.h>
#include <ESP8266WiFi.h>
 
String apiKey = "O54IVHCUBLMPKMWD";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "ALPHA 1";     // replace with your wifi ssid and wpa2 key
const char *pass =  "wologito37";
const char* server = "api.thingspeak.com";
 
#define DHTPIN D5          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);
 
WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
       
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}
 
void loop() 
{
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {     
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
          Serial.println("Waiting...");
          
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
```
</details>

## Hasil Percobaan

#### Serial Monitor
<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-6/serial%20monitor.jpg"   alt="rangkaian" width="500">

#### Thingspeak
<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-6/thingspeak.jpg"   alt="rangkaian" width="500">
<br>
<a href="https://thingspeak.com/channels/1997038" target="_blank">thingspeak.com/channels/1997038</a>


## Analisa
 
 Pada percobaan kali ini, digunakan protokol HTTP/REST dan server Thingspeak. REST atau Representational State Transfer adalah gaya arsitekturial dan pendekatan komunikasi yang bersifat stateless dan menggunakan HTTP/HTTPS untuk transmisi data. API yang menggunakan protokol REST disebut RESTful API. Pada percobaan ini, metode yang digunakan cukup sederhana, yaitu ESP32 hanya mengirimkan data sensor DHT11 ke server Thingspeak. Seperti pada percobaan sebelumnya, ESP32 harus tersambung pada jaringan WiFi.

 ```c
// Library yang dibutuhkan
#include <DHT.h>
#include <WiFi.h>

// Key Thingspeak
String apiKey = "O54IVHCUBLMPKMWD";   
 
// Informasi jaringan dan server Thingspeak 
const char *ssid =  "ALPHA 1";   
const char *pass =  "wologito37";
const char* server = "api.thingspeak.com";
 
// Pin DHT11 
#define DHTPIN D5       
DHT dht(DHTPIN, DHT11);
 
WiFiClient client;
```
Setelah semua informasi yang diperlukan telah didapat, maka ESP32 deberi perintah untuk menyambung dan mengirim data ke Thingspeak.
 
```c
 void loop() 
{
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {     
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
          Serial.println("Waiting...");
```
 
Saat ESP32 berhasil terhubung dan mengirim data ke Thingspeak. Hasil data sensor sudah bisa terbaca di Thingspeak.

## Kesimpulan
 
Dari percobaan yang telah dilakukan, didapat kesimpulan sebagai berikut:
 
- ESP32 dapat berkomunikasi melalui internet melalui suatu protokol. Protokol merupakan peraturan atau prosedur untuk mengirimkan sebuah data pada perangkat elektronik.

- Protokol HTTP/REST merupakan salah satu protokol yang dapat digunakan ESP32 untuk berkomunkasi melalui internet. Protokol ini memiliki kelebihan yaitu memungkinkan untuk melakukan operasi CRUD (create, read, update, delete). Namun dengan kelemahan membutuhkan bandwidth yang lebih tinggi dari protokol MQTT.
