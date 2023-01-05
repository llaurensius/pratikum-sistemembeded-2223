# Analisa

## Membaca Sensor DHT11
```c
//Library yang dibutuhkan
#include "DHT.h"

//Pin yang terkoneksi dengan Sensor DHT
#define DHTPIN 4

//Tipe DHT yang digunakan
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE); //Inisialisasi DHT dengan PIN
void setup() {

//Inisialisasi Serial Monitor untuk debugging
 Serial.begin(9600);
 Serial.println(F("DHT11 Embedded System Test!"));
 // Inisialisasi DHT
 dht.begin();
}
void loop() {
 //Membaca nilai Sensor dari DHT11
 delay(2000);
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 float h = dht.readHumidity();
 // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
 // Read temperature as Fahrenheit (isFahrenheit = true)
 float f = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);
 
 //Print nilai data yang telah dibaca dari sensor ke serial monitor
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


## Membaca Sensor DHT11 sebagai input untuk menjalankan LED Running
```c
//Library yang dibutuhkan
#include "DHT.h"

//Pin yang terkoneksi dengan sensor DHT
#define DHTPIN 4

//Tipe DHT yang digunakan
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

//Pin yang terkoneksi dengan LED
const int ledPin1 = 16;
const int ledPin2 = 18;
const int ledPin3 = 19;

void setup() {
//Inisialisasi Serial Monitor untuk debugging
 Serial.begin(9600);
 Serial.println(F("DHT11 Embedded System Test!"));
 dht.begin(); //Inisialisasi DHT
 
 //Memberikan perintah LED sebagai output
   pinMode (ledPin1, OUTPUT);
   pinMode (ledPin2, OUTPUT);
   pinMode (ledPin3, OUTPUT);

}
void loop() {
 //Membaca sensor DHT 
 delay(2000);
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 float h = dht.readHumidity();
 // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
 // Read temperature as Fahrenheit (isFahrenheit = true)
 float f = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);
  
  //Logika IF untuk membuat jika suhu dibawah 30° C maka LED akan berjalan running, ketika suhu diatas 30° C maka LED akan mati
  if(t < 30){
Serial.println(" - LED on");
    digitalWrite(ledPin1, HIGH);
    delay(500);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    delay(500);
    digitalWrite(ledPin3, LOW);
  }
  else{
    // turn LED off
    digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
    Serial.println(" - LED off");
  }
 
 //Print nilai sensor di serial monitor
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
# Kesimpulan
Sensor DHT11 berfungsi untuk membaca kelembapan dan suhu yang dapat di ESP32 untuk mengumpulkan data dan menjadikannya sebuah input untuk sebuah sistem seperti dalam contoh jika suhu dibawah 30° C maka LED akan berjalan runnning.

Sensor DHT11 memiliki delay pembacaan sekitar 2 detik sehingga pembacaan realtime dengan di serial monitor akan mengalami delay. Sensor DHT memiliki beberapa tipe dan tipe yang dipakai dalam pratikum ini adalah DHT11

# Dokumentasi



https://user-images.githubusercontent.com/118155742/210385142-87b808a2-a457-49f1-92b7-c72cc9861d21.mp4



https://user-images.githubusercontent.com/118155742/210385152-b694ddc9-3420-4c04-ad43-1d4f44853ff2.mp4






