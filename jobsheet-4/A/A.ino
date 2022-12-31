#include "CayenneMQTTESP32.h" // ganti tanda " dengan > jika program error
#include "DHT.h"
//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#define DHTPIN 4     // what digital pin we're connected to
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// WiFi network info.
char ssid[] = "home-mnl";
char wifiPassword[] = "h0m3-121";
const int ledPin = 16;

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "9f1901b0-7f54-11ed-b193-d9789b2af62b";
char password[] = "15d7c1af5defe0be2d748a44ebec74251ae13b9e";
char clientID[] = "82f43c00-8749-11ed-b193-d9789b2af62b";

unsigned long lastMillis = 0;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}
float h, t, f;
void loop() {
  Cayenne.loop();

  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

}

//Mengirimkan data ke MQTT Cayenne dan menampilkannya di Dashboard Aplikasi Cayenne
CAYENNE_OUT(1)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Suhu %f C", 1, t);
  Cayenne.celsiusWrite(1, t);
}
CAYENNE_OUT(2)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Hum %f ", 2, h);
  Cayenne.virtualWrite(2, h);
}
CAYENNE_IN(3)
{
  digitalWrite(ledPin, !getValue.asInt());  // to get the value from the website
}
