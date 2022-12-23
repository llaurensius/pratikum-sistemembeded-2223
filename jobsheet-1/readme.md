
# Jobsheet 1 
DASAR PEMROGRAMAN ESP32 UNTUK PEMROSESAN DATA INPUT/OUTPUT ANALOG DAN DIGITAL

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)


## Anggota Kelompok

- [Azarya Paska Saputra - 4.31.20.0.05](https://github.com/azpaska)
- [Laurensius Liquori - 4.31.20.0.13](https://github.com/llaurensius)

## Analisa

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

