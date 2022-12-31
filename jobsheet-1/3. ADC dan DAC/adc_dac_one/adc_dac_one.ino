// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin = 34;
// variable for storing the potentiometer value 
int potValue = 0;
int volt;
void setup() {
Serial.begin(115200);
delay(1000); 
}
void loop() {
// Reading potentiometer value 
potValue = analogRead(potPin); 
delay(500);
volt = potValue*5/4095;
Serial.println("Nilai ADC");
Serial.println(potValue);
Serial.println("Nilai Tegangan");
Serial.println(volt);
}
