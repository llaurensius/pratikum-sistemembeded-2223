
# Jobsheet 4 
Cayenne (MQTT) + SENSOR (DHT11) + LED (ON/OFF) + BUTTON di website monitoring

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

## Analisa
Dalam percobaan kali ini menggunakan ESP32 yang terpasang sensor DHT11 berfungsi untuk membaca Suhu dan Temperature kemudian diteruskan oleh ESP32 melalui protokol MQTT (Cayenne) untuk agar bisa terhubung dan berkomunikasi antar mesin.

Library yang dibutuhkan adalah 
```
#include "CayenneMQTTESP32.h" // ganti tanda " dengan > jika program error
#include "DHT.h"
//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
```
