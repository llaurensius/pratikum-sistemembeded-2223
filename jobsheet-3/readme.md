# Jobsheet 3: Topologi Jaringan Lokal dan Wifi

## Anggota Kelompok
- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

## Daftar Isi
  * [Hasil Percobaan](#hasil-percobaan)
  * [Analisa](#analisa)
  * [Kesimpulan](#kesimpulan)


## Hasil Percobaan
    A.	ESP32 Wi-Fi Modes dan Wifi-Scan
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
![js3.1](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.1/3.1.jpg)

    B. Menghubungkan ESP32 dengan Jaringan WiFi
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
    


## Analisa

## Kesimpulan
