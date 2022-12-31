# Analisa
a-capasitivetouchsensor
```
// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4. 
void setup() {
Serial.begin(115200);
delay(1000); // give me time to bring up serial monitor 
Serial.println("ESP32 Touch Test");
}
void loop() {
Serial.println(touchRead(4));  // get value of Touch 0 pin = GPIO 4 
delay(1000);
}
```

a-capasitivetouchsensorled1
```
// set pin numbers
const int touchPin = 4; 
const int ledPin = 16;

// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;

void setup(){
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  // initialize the LED pin as an output:
  pinMode (ledPin, OUTPUT);
}

void loop(){
  // read the state of the pushbutton value:
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(touchValue < threshold){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED off");
  }
  delay(500);
}
```


a-capasitivetouchsensorled2
```
// set pin numbers
const int touchPin = 4; 
const int ledPin1 = 16;
const int ledPin2 = 18;
const int ledPin3 = 19;

// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;

void setup(){
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  // initialize the LED pin as an output:
  pinMode (ledPin1, OUTPUT);
  pinMode (ledPin2, OUTPUT);
  pinMode (ledPin3, OUTPUT);
}

void loop(){
  // read the state of the pushbutton value:
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(touchValue < threshold){
    // turn LED on
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
  delay(500);
}
```
# Kesimpulan
Pratikum ini memberikan kesimpulan bahwa dalam pemanfaatan ESP32 sebagai mikrokontroller dapat membaca sensor berupa sentuhan kemudian dari sentuhan itu dapat diberikan output dalam contoh ini akan menghidupkan LED dan membuat LED running dari kiri ke kanan.


# Dokumentasi

https://user-images.githubusercontent.com/118155742/210125150-58dc840f-62fe-4d66-9bfc-5c341c3bf518.mp4

https://user-images.githubusercontent.com/118155742/210124792-97a59261-6ea1-417b-9615-5e0ab913d949.mp4





