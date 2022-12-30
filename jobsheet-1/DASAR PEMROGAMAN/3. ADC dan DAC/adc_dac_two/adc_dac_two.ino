// These constants won't change. They're used to give names to the pins used: 
const int analogInPin = 34;  // Analog input pin that the potentiometer is attached to 
const int analogOutPin = 5; // Analog output pin that the LED is attached to
// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out) 
void setup() {
Serial.begin(115200); // initialize serial communications at 115200 bps: 
// configure LED PWM functionalitites
ledcSetup(ledChannel, freq, resolution);
// attach the channel to the GPIO to be controlled 
ledcAttachPin(analogOutPin, ledChannel);
}
void loop() {
sensorValue = analogRead(analogInPin); // read the analog in value:
outputValue = map(sensorValue, 0, 4095, 0, 255); // map it to the range of the analog out:
ledcWrite(ledChannel, outputValue); // change the analog out value:
// print the results to the Serial Monitor:
Serial.print("sensor = ");
Serial.print(sensorValue);
Serial.print("\t output = ");
Serial.println(outputValue);
// wait 2 milliseconds before the next loop for the analog-to-digital 
// converter to settle after the last reading:
delay(500);
}
