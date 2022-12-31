#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0xBB, 0x3A, 0x94};
// Define variables
float temperature;
float humidity;
// Define variables to store incoming readings
float incomingTemp;
float incomingHum;
// Variable to store if sending data was successful
String success;
//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
 float temp;
 float hum;
} struct_message;
// Create a struct_message sensors reading
struct_message DHTReadings;
// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;
esp_now_peer_info_t peerInfo;
// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
 Serial.print("\r\nLast Packet Send Status:\t");
 Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
 if (status ==0){
 success = "Delivery Success :)";
 }
 else{
 success = "Delivery Fail :(";
 }
}
// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
 memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
 Serial.print("Bytes received: ");
 Serial.println(len);
 incomingTemp = incomingReadings.temp;
 incomingHum = incomingReadings.hum;
}
void setup() {
 // Init Serial Monitor
 Serial.begin(115200);
 // Init DHT
 dht.begin();
 // Set device as a Wi-Fi Station
 WiFi.mode(WIFI_STA);
 // Init ESP-NOW
 if (esp_now_init() != ESP_OK) {
 Serial.println("Error initializing ESP-NOW");
 return;
 }
 // Once ESPNow is successfully Init, we will register for Send CB to
 // get the status of Trasnmitted packet
 esp_now_register_send_cb(OnDataSent);

 // Register peer
 memcpy(peerInfo.peer_addr, broadcastAddress, 6);
 peerInfo.channel = 0;
 peerInfo.encrypt = false;

 // Add peer
 if (esp_now_add_peer(&peerInfo) != ESP_OK){
 Serial.println("Failed to add peer");
 return;
 }
 // Register for a callback function that will be called when data is received
 esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
 delay(2000);
 getReadings();
 // Set values to send
 DHTReadings.temp = temperature;
 DHTReadings.hum = humidity;
 // Send message via ESP-NOW
 esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &DHTReadings,
sizeof(DHTReadings));

 if (result == ESP_OK) {
 Serial.println("Sent with success");
 }
 else {
 Serial.println("Error sending the data");
 }

 delay(1000);
}
void getReadings(){
 float t = dht.readTemperature();
 float h = dht.readHumidity();
 float f = dht.readTemperature(true);
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 Serial.print(F("Humidity: "));
 Serial.print(h);
 Serial.print(F("% Temperature: "));
 Serial.print(t);
 Serial.print(F("°C "));
}
