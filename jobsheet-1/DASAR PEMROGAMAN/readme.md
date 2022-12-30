
# Jobsheet 1 
DASAR PEMROGRAMAN ESP32 UNTUK PEMROSESAN DATA INPUT/OUTPUT ANALOG DAN DIGITAL

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

## Analisa BLINK

Fungsi void setup() dijalankan pada saat sketch atau program Arduino mulai. Fungsi ini digunakan untuk menginisiasi variabel, mendeklarasikan pin yang digunakan, menggunakan library, dll.

```
void setup() {
 ```
 
Fungsi pinMode adalah menginisiasi GPIO yang akan dijadikan output.

 ```
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(5, OUTPUT);
}
```

Fungsi void loop() dijalankan setelah fungsi setup() sudah selesai dijalankan, void loop() bertujuan untuk mengeksekusi dan menjalankan program yang sudah dibuat. Fungi ini akan secara aktif mengontrol board ESP32 membaca input atau merubah output.

```
void loop() {
```

Fungsi digitalWrite adalah mengeksesi output (LED) untuk hidup dan mati.
Fungsi dari delay adalah mengatur waktu berhenti sebelum mengeksekusi perintah selanjutnya.
```
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(5,LOW);    // turn the LED off by making the voltage LOW
  delay(100);     
```

Dalam percobaan selanjutnya LED akan berubah ubah jeda waktu antara hidup dan matinya


## Analisa Push Button
Fungsi void setup() dijalankan pada saat sketch atau program Arduino mulai. Fungsi ini digunakan untuk menginisiasi variabel, mendeklarasikan pin yang digunakan, menggunakan library, dll.

```
void setup() {
```
 
Fungsi void loop() dijalankan setelah fungsi setup() sudah selesai dijalankan, void loop() bertujuan untuk mengeksekusi dan menjalankan program yang sudah dibuat. Fungi ini akan secara aktif mengontrol board EPS32 baik membaca input atau merubah output.

```
void loop() {
```

Menginisiasi input dari ESP32 yang akan dibaca oleh ESP dengan perintah. Button akan terhubung di pin 15,2,4 dari ESP32 dan LED akan keluar pada 5,18,19
```
const int buttonPin1 = 15;  // the number of the pushbutton pin 
const int buttonPin2 = 2;
const int buttonPin3 = 4;
const int ledPin1 =  5;    // the number of the LED pin
const int ledPin2 =  18;
const int ledPin3 =  19;
```