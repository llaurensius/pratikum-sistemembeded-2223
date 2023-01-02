# Jobsheet 1.1
JARINGAN SENSOR NIRKABEL MENGGUNAKAN ESP-NOW

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

# Analisa
Dalam pratikum ini menggunakan 4 buah ESP32 yang terdiri dari 3 sebagai sender/transmitter dan 1 sebagai receiver/koordinator

## Transmitter
```c
#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0x24, 0x6F, 0x28, 0x02, 0xC3, 0x1C}; //24:6F:28:02:C3:1C
uint8_t broadcastAddress2[] = {0x24, 0x0A, 0xC4, 0XC6, 0x06, 0x54}; //24:0A:C4:C6:06:54
uint8_t broadcastAddress3[] = {0x8C, 0xCE, 0x4E, 0xC8, 0x29, 0x1B}; //8C:CE:4E:C8:29:1B

typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct test;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
   
  // register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // register second peer  
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  /// register third peer
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  test_struct test1;
  test_struct test2;
  test_struct test3;
  
  test1.x = random(0,20);
  test1.y = random(0,20);

  test2.x = random(0,20);
  test2.y = random(0,20);

  test2.x = random(0,20);
  test2.y = random(0,20);
 
  esp_err_t result1 = esp_now_send(broadcastAddress1, (uint8_t *) &test1, sizeof(test_struct));
   
  if (result1 == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  esp_err_t result2 = esp_now_send(
  broadcastAddress2, 
  (uint8_t *) &test2,
  sizeof(test_struct));

if (result2 == ESP_OK) {
  Serial.println("Sent with success");
}
else {
  Serial.println("Error sending the data");
}

  esp_err_t result3 = esp_now_send(
  broadcastAddress3, 
  (uint8_t *) &test3,
  sizeof(test_struct));

if (result3 == ESP_OK) {
  Serial.println("Sent with success");
}
else {
  Serial.println("Error sending the data");
}
  delay(2000);

  
}
```

## Receiver
```c
#include <esp_now.h> 
#include <WiFi.h>
//Structure example to receive data 
//Must match the sender structure 
typedef struct test_struct {
int x; 
int y;
} test_struct;
//Create a struct_message called test 
test_struct test;
//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { 
memcpy(&test, incomingData, sizeof(test));
Serial.print("Bytes received: ");
Serial.println(len);
Serial.print("x: ");
Serial.println(test.x);
Serial.print("y: ");
Serial.println(test.y);
Serial.println(); 
}
void setup() {
//Initialize Serial Monitor 
Serial.begin(115200);
//Set device as a Wi-Fi Station 
WiFi.mode(WIFI_STA);
//Init ESP-NOW
if (esp_now_init() != ESP_OK) {
  Serial.println("Error initializing ESP-NOW"); 
return;
}
// Once ESPNow is successfully Init, we will register for recv CB to 
// get recv packer info
esp_now_register_recv_cb(OnDataRecv); 
}
void loop() { 
}
```
# Kesimpulan


# Dokumentasi


