# Jobsheet 3: Topologi Jaringan Lokal dan Wifi

## Anggota Kelompok
- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

## Daftar Isi
  * [Hasil Percobaan](#hasil-percobaan)
  * [Analisa](#analisa)
  * [Kesimpulan](#kesimpulan)


## Hasil Percobaan

#### A.	ESP32 Wi-Fi Modes dan Wifi-Scan
<details>
  <summary>Program (click to open)</summary>

```c
#include "WiFi.h"
void setup() {
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
}
void loop() {
  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
  Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
      }
  }
  Serial.println("");
  // Wait a bit before scanning again
  delay(5000);
}
```
</details>
 
 
*Serial Monitor*
![js3.1](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.1/3.1.jpg)

#### B. Menghubungkan ESP32 dengan Jaringan WiFi
<details>
  <summary>Program (click to open)</summary>
 
 ```c
    #include <WiFi.h>
    // Replace with your network credentials (STATION)
    const char* ssid = "ka";
    const char* password = "123456788";
    void initWiFi() {
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      Serial.print("Connecting to WiFi ..");
      while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
      }
    Serial.println(WiFi.localIP());
    }
    void setup() {
      Serial.begin(115200);
      initWiFi();
      Serial.print("RRSI: ");
      Serial.println(WiFi.RSSI());
      }
    void loop() {
     // put your main code here, to run repeatedly:
    }
```
</details>
 
 
*Serial Monitor*
![js3.2](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.2/3.2.jpg)

#### C.	Menghubungkan Kembali (Re-connect) ESP32 dengan Jaringan Wi-Fi
<details>
  <summary>Program (click to open)</summary>
 
```c
#include <WiFi.h>

// Replace with your network credentials (STATION)
const char* ssid = "ka";
const char* password = "123456788";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}

void loop() {
  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}
```
</details>
 
*Serial Monitor*
![js3.3](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.3/js3.3.jpg)

#### D.	Mengganti Hostname ESP32
<details>
  <summary>Program (click to open)</summary>
 
```c
#include <WiFi.h>
// Replace with your network credentials (STATION)
const char* ssid = "ka";
const char* password = "123456788";
String hostname = "ESP32 Node Temperature";
void initWiFi() {
 WiFi.mode(WIFI_STA);
 WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
 WiFi.setHostname(hostname.c_str()); //define hostname
 //wifi_station_set_hostname( hostname.c_str() );
 WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi ..");
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print('.');
 delay(1000);
 }
 Serial.println(WiFi.localIP());
}
void setup() {
 Serial.begin(115200);
 initWiFi();
 Serial.print("RRSI: ");
 Serial.println(WiFi.RSSI());
}
void loop() {
 // put your main code here, to run repeatedly:
}
```
</details>
 
*Hasil*<br /><br />
![js3.4](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.4/js3.4.jpg)

#### E.	Mengirim Data Sensor ke Database<br /><br />
<details>
  <summary>Program (click to open)</summary>
 
```c
// Import required libraries
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
// Replace with your network credentials
const char* ssid = "ka";
const char* password = "123456788";
#define DHTPIN 32 // Digital pin connected to the DHT sensor
// Uncomment the type of sensor in use:
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
String readDHTTemperature() {
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
 // Read temperature as Fahrenheit (isFahrenheit = true)
 //float t = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).
 if (isnan(t)) {
 Serial.println("Failed to read from DHT sensor!");
 return "--";
 }
 else {
 Serial.println(t);
 return String(t);
}
}
String readDHTHumidity() {
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 float h = dht.readHumidity();
 if (isnan(h)) {
 Serial.println("Failed to read from DHT sensor!");
 return "--";
 }
 else {
 Serial.println(h);
 return String(h);
 }
}
```
```html
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
 <meta name="viewport" content="width=device-width, initial-scale=1">
 <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css"
 integrity="sha384-
 fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr"
 crossorigin="anonymous">
  <style>
   html {
   font-family: Arial;
   display: inline-block;
   margin: 0px auto;
   text-align: center;
   }
   h2 { font-size: 3.0rem; }
   p { font-size: 3.0rem; }
   .units { font-size: 1.2rem; }
   .dht-labels{
   font-size: 1.5rem;
   vertical-align:middle;
   padding-bottom: 15px;
   }
  </style>
</head>
<body>
 <h2>ESP32 DHT Server</h2>
 <p>
 <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
 <span class="dht-labels">Temperature</span>
 <span id="temperature">%TEMPERATURE%</span>
 <sup class="units">&deg;C</sup>
 </p>
 <p>
 <i class="fas fa-tint" style="color:#00add6;"></i>
 <span class="dht-labels">Humidity</span>
 <span id="humidity">%HUMIDITY%</span>
 <sup class="units">&percnt;</sup>
 </p>
</body>
<script>
 setInterval(function ( ) {
 var xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
 if (this.readyState == 4 && this.status == 200) {
 document.getElementById("temperature").innerHTML = this.responseText;
 }
 };
 xhttp.open("GET", "/temperature", true);
 xhttp.send();
 }, 10000 ) ;
 setInterval(function ( ) {
 var xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
 if (this.readyState == 4 && this.status == 200) {
 document.getElementById("humidity").innerHTML = this.responseText;
 }
 };
 xhttp.open("GET", "/humidity", true);
 xhttp.send();
 }, 10000 ) ;
</script>
</html>)rawliteral";
```
```c
// Replaces placeholder with DHT values
String processor(const String& var){
 //Serial.println(var);
 if(var == "TEMPERATURE"){
 return readDHTTemperature();
 }
 else if(var == "HUMIDITY"){
 return readDHTHumidity();
 }
 return String();
}
void setup(){
 // Serial port for debugging purposes
 Serial.begin(115200);
 dht.begin();

 // Connect to Wi-Fi
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(1000);
 Serial.println("Connecting to WiFi..");
 }
 // Print ESP32 Local IP Address
 Serial.println(WiFi.localIP());
 // Route for root / web page
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send_P(200, "text/html", index_html, processor);
 });
 server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send_P(200, "text/plain", readDHTTemperature().c_str());
 });
 server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send_P(200, "text/plain", readDHTHumidity().c_str());
 });
 // Start server
 server.begin();
}
void loop(){

}
```
</details>
 
*Serial Monitor*<br /><br />
![sm](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.5/js3.5.jpg)<br /><br />
*Tampilan Web PC*<br /><br />
![pc](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.5/web.jpg)<br /><br />
*Tampilan Web Smartphone*<br /><br />
<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.5/web%20hp.jpg" alt="hp" height="500px">
    


## Analisa

#### A.	ESP32 Wi-Fi Modes dan Wifi-Scan
 
 <img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.1/flowchart3.1.png" align="right"
     alt="Flowchart" height="300">
 
Pada ESP32, terdapat 3 mode akses untuk Wifi, yaitu WIFI_STA (station mode : ESP32 sebagai client yang terkoneksi ke access point), WIFI_AP (access point mode : ESP32 berperan sebagai access point), WIFI_STA_AP (access point and station : ESP32 dapat terkoneksi dengan access point yang lain). Pada percobaan kali ini, ESP32 digunakan sebagai client.
 
Untuk menjadikan ESP32 sebagai client, mode pada program yang digunakan yaitu WIFI_STA
 
 ```c
 void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // mode akses station
  WiFi.disconnect(); // untuk memutus koneksi dengan access point sebelumnya
  delay(100);
  Serial.println("Setup done");
}
 ```
 Setelah terinisiasi, ESP32 sudah dalam mode station. Selanjutnya ESP32 akan melakukan scan network untuk melihat jaringan wifi sekitar beserta kekuatan sinyal atau RSSI. Dalam program ini, ESP32 hanya difungsikan untuk scan network dan belum mendapat perintah untuk terhubung pada known network.
 
 #### B. Menghubungkan ESP32 dengan Jaringan WiFi
 
 <img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.2/flowchart3.2.png" align="right"
     alt="Flowchart" height="300">
 
 Pada percobaan kali ini, ESP32 digunakan sebagai client dan terhubung ke suatu jaringan WiFi. Seperti pada percobaan A. ESP32 Wi-Fi Modes dan Wifi-Scan, untuk percobaan kedua program ditambahkan informasi mengenai jaringan yang akan disambung.
 
 ```c
 #include <WiFi.h>
const char* ssid = "ka"; // SSID atau nama jaringan WiFi yang akan disambungkan
const char* password = "123456788"; // password WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA); // perintah untuk mode akses client
  WiFi.begin(ssid, password); // perintah untuk connect berdasarkan informasi SSID dan password yang sudah diberikan
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print('.');
  delay(1000);
  }
Serial.println(WiFi.localIP());
}
 ```
 
 Ketika scanning network dan ditemukan known network atau jaringan WiFi yang sudah diberikan pada program, ESP32 akan mencoba untuk terhubung. Saat gagal untuk menemukan knwon network, ESP32 akan terus melakukan scanning dan saat gagal untuk terhubung ESP32 akan terus mencoba untuk menghubungkan.
 
 #### C.	Menghubungkan Kembali (Re-connect) ESP32 dengan Jaringan Wi-Fi
 
 <img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.3/flowchart3.3.png" align="right"
     alt="Flowchart" height="300">
 
  Melanjutkan dari percobaan sebelumnya, pada percobaan kali ini ESP32 digunakan sebagai client dan terhubung ke suatu jaringan WiFi. Seperti pada percobaan B. Menghubungkan ESP32 dengan Jaringan WiFi, untuk percobaan ketiga program ditambahkan perintah untuk melakukan rekoneksi ketika jaringan terputus. Pada percobaan B ketika jaringan terputus maka ESP32 tidak akan melakukan rekoneksi karena belum terdapat perintah untuk rekoneksi, untuk percobaan ini ditambahkan perintah untuk melakukan rekoneksi.
 
 ```c
 void loop() {
  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
 ```
 ESP32 akan mengecek secara berkala berdasarkan waktu interval yang telah ditentukan
 
  ```c
unsigned long previousMillis = 0;
unsigned long interval = 30000;
 ```
 
 Saat didapati bahwa ESP32 terputus dari jaringan WiFi maka ESP32 akan mencoba untuk melakukan rekoneksi hingga terhubung kembali.
 
 #### D. 	Mengganti Hostname ESP32
 
 <img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.4/flowchart3.4.png" align="right"
     alt="Flowchart" height="300">
 
 Melanjutkan dari percobaan sebelumnya, pada percobaan ini hanya ditambahkan perintah untuk mengubah hostname atau nama ESP32 yang terlihat pada jaringan. Dari program sebelumnya hanya ditambahkan baris perintah untuk informasi nama hostname dan baris perintah inisialisasi.
 
 ```c
const char* ssid = "ka";
const char* password = "123456788";
String hostname = "ESP32 Node Temperature"; // informasi nama hostname yang akan digunakan
void initWiFi() {
 WiFi.mode(WIFI_STA);
 WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
 WiFi.setHostname(hostname.c_str()); // inisialisasi hostname
 WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi ..");
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print('.');
 delay(1000);
 }
 Serial.println(WiFi.localIP());
}
  ```
 
 Ketika didapati bahwa baris program untuk mengatur hostname tidak singkron, atau tidak tepat maka hostname ESP32 tidak akan berubah dan tetap menggunakan default hostname.
 
#### E. Mengirim Data Sensor ke Database
 
<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.5/flowchart3.5.png" align="right"
     alt="Flowchart" height="300">
 
 Pada percobaan kali ini, dilakukan percobaa mengirim data sendor ke database melalui jaringan WiFi. Metode penyambungan ke jaringan WiFi menggunakan seperti pada percobaan sebelumnya. Namun pada percobaan ini ditambahkan sensor untuk dikirimkan ke database. 
 
```c 
#include <WiFi.h> // library untuk menggunakan WiFi
#include <ESPAsyncWebServer.h> // library untuk web server yang digunakan sebagai interface database
#include <Adafruit_Sensor.h> // library untuk mengirim data sensor
#include <DHT.h> // library untuk membaca sensor
 ```
Kemudian dilakukan inisisalisasi seperti pada percobaan sebelumnya dan percobaan pembacaan <a href="https://github.com/llaurensius/pratikum-sistemembeded-2223/blob/main/jobsheet-2/2.%20Mengakses%20Sensor%20DHT%2011%20(Single%20Wire%20atau%20BUS)/readme.md" target="_blank">sensor DHT</a>

<img src="https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.5/skematik.jpg" align="center"
     alt="Skematik" height="200">

 

 
 
## Kesimpulan

## Tugas
