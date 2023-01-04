# Jobsheet 1.1
JARINGAN SENSOR NIRKABEL MENGGUNAKAN ESP-NOW



## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

# Analisa

Dalam praktikum ini, digunakan 2 buah ESP32 agar dapat saling berkomuniasi secara dua arah.

## A. Membaca Sensor DHT11 

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


# Kesimpulan


# Dokumentasi
## DHT11 Read
![500000](https://user-images.githubusercontent.com/118155742/210127901-444d1674-53e9-433c-8b2d-fafd67f2d557.jpg)

Dokumentasi Video

[![Dokumentasi Receive](https://img.shields.io/badge/YouTube-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)](https://youtube.com/shorts/u8l7PD0T5oc?feature=share)

## Tx & Rx DHT11 Data
![test](https://user-images.githubusercontent.com/118155742/210127905-9a06ed43-51f1-4c68-a107-5ef8157ab890.jpg)

Dokumentasi Video

[![Dokumentasi Transmitter](https://img.shields.io/badge/YouTube-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)](https://youtube.com/shorts/mjIHEiJML1Q?feature=share)
