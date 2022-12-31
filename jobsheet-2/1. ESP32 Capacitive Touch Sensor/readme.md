# Analisa
a-capasitivetouchsensor - Hanya membaca sentuhan yang dilakukan dan menampilkan di serial monitor
```
// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4. 
void setup() {
Serial.begin(115200);
delay(1000); // give me time to bring up serial monitor 
Serial.println("ESP32 Touch Test");
}
void loop() {
Serial.println(touchRead(4));  // menampilkan nilai dari sentuhan yang ada di pin GPIO 4
delay(1000);
}
```


a-capasitivetouchsensorled1 - Jika disentuh maka LED akan menyala ketika disentuh dan tidak menyala jika tidak disentuh
```
// menginisiasi pin GPIO yang akan dipakai
const int touchPin = 4; //Pin GPIO yang mendeteksi sentuhan
const int ledPin = 16; //Pin GPIO yang akan menyalan LED sebagai keluaran

// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;

void setup(){
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  // Inisiasi LED sebagai keluaran
  pinMode (ledPin, OUTPUT);
}

void loop(){
  // membaca sensor sentuhan
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // mengecek apakah ada nilai dari sentuhan
  // jika ada maka LED akan menyala
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


a-capasitivetouchsensorled2 - LED Running
```
// menginisiasi pin GPIO yang akan dipakai
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
  // menginisiasi pin GPIO LED sebagai keluaran
  pinMode (ledPin1, OUTPUT);
  pinMode (ledPin2, OUTPUT);
  pinMode (ledPin3, OUTPUT);
}

void loop(){
  // membaca nilai sentuhan
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // mengecek dengan logika IF ELSE dan akan menyalan LED jika terdapat sentuhan
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





