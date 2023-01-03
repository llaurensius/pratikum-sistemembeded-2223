
# Jobsheet 1 
DASAR PEMROGRAMAN ESP32 UNTUK PEMROSESAN DATA INPUT/OUTPUT ANALOG DAN DIGITAL


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

## Analisa BLINK

Fungsi void setup() dijalankan pada saat sketch atau program Arduino mulai. Fungsi ini digunakan untuk menginisiasi variabel, mendeklarasikan pin yang digunakan, menggunakan library, dll.

```c
void setup() {
 ```
 
Fungsi pinMode adalah menginisiasi GPIO yang akan dijadikan output.

 ```c
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(5, OUTPUT);
}
```

Fungsi void loop() dijalankan setelah fungsi setup() sudah selesai dijalankan, void loop() bertujuan untuk mengeksekusi dan menjalankan program yang sudah dibuat. Fungi ini akan secara aktif mengontrol board ESP32 membaca input atau merubah output.

```c
void loop() {
```

Fungsi digitalWrite adalah mengeksesi output (LED) untuk hidup dan mati.
Fungsi dari delay adalah mengatur waktu berhenti sebelum mengeksekusi perintah selanjutnya.
```c
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(5,LOW);    // turn the LED off by making the voltage LOW
  delay(100);     
```

Dalam percobaan selanjutnya LED akan berubah ubah jeda waktu antara hidup dan matinya


## Analisa Push Button
Fungsi void setup() dijalankan pada saat sketch atau program Arduino mulai. Fungsi ini digunakan untuk menginisiasi variabel, mendeklarasikan pin yang digunakan, menggunakan library, dll.

```c
void setup() {
```
 
Fungsi void loop() dijalankan setelah fungsi setup() sudah selesai dijalankan, void loop() bertujuan untuk mengeksekusi dan menjalankan program yang sudah dibuat. Fungi ini akan secara aktif mengontrol board EPS32 baik membaca input atau merubah output.

```c
void loop() {
```

Menginisiasi input dari ESP32 yang akan dibaca oleh ESP dengan perintah. Button akan terhubung di pin GPIO 15,2,4 dari ESP32 dan LED akan keluar pada pin GPIO 5,18,19
```c
const int buttonPin1 = 15;  // the number of the pushbutton pin 
const int buttonPin2 = 2;
const int buttonPin3 = 4;
const int ledPin1 =  5;    // the number of the LED pin
const int ledPin2 =  18;
const int ledPin3 =  19;
```

Buat variabel untuk menahan status button dengan nilai bawaan adalah 0
```c
int buttonState = 0;
```

Kemudian didefinisikan Button sebagai Input dan LED sebagai Output
```c
pinMode(buttonPin1, INPUT);
pinMode(buttonPin2, INPUT);
pinMode(buttonPin3, INPUT);
// initialize the LED pin as an output 
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
```

Buat logika untuk menjalankan perintah dimana button 1 ketika ditekan maka LED pertama akan menyalan beberapa saat, kemudian jika button 2 ditekan maka LED akan melakukan BLINK dan jika button 3 ditekan maka LED akan berjalan running dari Kiri ke Kanan
```c
// read the state of the pushbutton value 
button1 = digitalRead(buttonPin1); 
button2 = digitalRead(buttonPin2); 
button3 = digitalRead(buttonPin3); 
// check if the pushbutton is pressed. 
// if it is, the buttonState is HIGH 
if (button1 == HIGH) {
    digitalWrite(ledPin1, HIGH);
}  else if (button2 == HIGH){
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    delay(500);
} else if (button3 == HIGH) {
    digitalWrite(ledPin1, HIGH);
    delay(500);
    digitalWrite(ledPin1, LOW);
    delay(500);
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    delay(500);
    digitalWrite(ledPin3, HIGH);
    delay(500);
    digitalWrite(ledPin3, LOW);
    delay(500);
}
```

## Analisa PWM


Dalam Pemrogaman PWM kedua diberikan contoh untuk melihat efek PWM yaitu output lampu LED akan hidup dengan power dimulai dari 0% hingga 100% secara perlahan dan kembali dari 100% ke 0% secara perlahan dan berulang-ulang. Pada percobaan pertama diberikan contoh hanya dengan satu LED saja kemudian pada percobaan kedua diberikan contoh dengan 3 LED sekaligus

Fungsi dari input data ditunjukan dalam koding
```c
// increase the LED brightness
for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
// changing the LED brightness with PWM 
ledcWrite(ledChannel, dutyCycle);
delay(15); 
}
// decrease the LED brightness
for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){ 
// changing the LED brightness with PWM 
ledcWrite(ledChannel, dutyCycle);   
delay(15); 
}
```

## ADC DAC
Dalam pekerjaan Analog Digital Converter dan Digital Analog Converter dicontohkan dengan membaca input dari sebuah potensiometer yang diterjemahkan secara digital melalui pemrogaman sebagai berikut.
```c
potValue = analogRead(potPin); 
delay(500);
volt = potValue*5/4095;
Serial.println("Nilai ADC");
Serial.println(potValue);
Serial.println("Nilai Tegangan");
Serial.println(volt);
```
Fungsi ini akan membaca setiap putaran potensio dan menghasilkan angka sesuai dengan putaran potensiometer.

Percobaan ADC DAC kedua mengimplementasikan angka yang dibaca oleh ESP32 menjadi nyala lampu LED, jika potensiometer diputar yang paling kecil maka LED tidak menyala dan sebaliknya jika potensiometer diputar pada kapasitas maksimum maka LED akan nyala paling terang. Koding untuk percobaan kedua yang berfungsi untuk membaca dan memberikan perintah ke LED untuk menyala adalah sebagai berikut.
```c
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
```


# Dokumentasi
## GPIO


https://user-images.githubusercontent.com/118155742/210073882-773703e8-a648-4e19-9a5b-10b4a4c4d989.mp4


https://user-images.githubusercontent.com/118155742/210073946-857643b9-5e8f-4ddf-971d-5384ba1ee032.mp4


https://user-images.githubusercontent.com/118155742/210074050-b0654e84-c6df-43be-a71c-67f6915a760e.mp4


https://user-images.githubusercontent.com/118155742/210074079-f5f3c587-0153-4375-bdf1-30d8cec8c72b.mp4





## PWM
https://user-images.githubusercontent.com/118155742/210073593-e0bb21a0-879f-4291-b16d-23c9d7c4c185.mp4


https://user-images.githubusercontent.com/118155742/210074424-23869e47-c522-4863-9fd2-a46d586e8795.mp4


## ADC & DAC


https://user-images.githubusercontent.com/118155742/210075850-ed103514-8303-4f57-9a01-782e828895ee.mp4


![adc dac two](https://user-images.githubusercontent.com/118155742/210075481-813937f8-3c8a-42dd-a7f8-2ca4174be2db.jpg)
