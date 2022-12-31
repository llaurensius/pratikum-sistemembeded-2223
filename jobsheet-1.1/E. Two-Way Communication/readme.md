# Jobsheet 1.1
JARINGAN SENSOR NIRKABEL MENGGUNAKAN ESP-NOW

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

# Analisa
Dalam koding ini berfungsi untuk mengetahui MAC Address yang terdapat di ESP32
```
#include "WiFi.h" //library yang digunakan hanya WiFi.h
void setup(){
Serial.begin(115200);
WiFi.mode(WIFI_MODE_STA); //mengaktifkan mode WiFi Station
Serial.println(WiFi.macAddress()); //print MAC Address di Serial Monirot
}
void loop(){ 
}
```


# Kesimpulan
MAC Address diperlukan untuk identifikasi perangkat ESP32 dalam protokol komunikasi ESP-NOW, dengan MAC Address kita bisa mengirim data ke ESP32 lainnya melalui protokol ESP-NOW


# Dokumentasi

![MAC ADDRESS](https://user-images.githubusercontent.com/118155742/210126557-2fee30cf-cfcf-4cdf-b783-71a9ca477aa7.png)
