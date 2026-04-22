# README - Praktikum Modul 3: Protokol Komunikasi

**Nama:** Finda Wulan Febrianti
**NIM:** H1H024055

---

## 🔹 Deskripsi Praktikum

Praktikum ini bertujuan untuk memahami penggunaan protokol komunikasi serial pada Arduino, yaitu **UART** dan **I2C**. UART digunakan untuk komunikasi antara Arduino dan komputer, sedangkan I2C digunakan untuk komunikasi antara Arduino dengan perangkat eksternal seperti LCD.

---

# 🔹 Percobaan 3A - UART

##  Dokumentasi Rangkaian

![alt text](<percobaan 1(3).jpeg>)
---

## Serial Monitor

![alt text](<percobaan1 tekan 1(3).jpeg>)

---

## Jawaban Pertanyaan

### 1. Proses dari input keyboard hingga LED menyala/mati

Proses dimulai dari pengguna yang memasukkan karakter melalui keyboard pada Serial Monitor di Arduino IDE. Data tersebut dikirim melalui komunikasi serial (UART) ke Arduino dalam bentuk data byte.

Arduino kemudian mengecek apakah data tersedia menggunakan fungsi `Serial.available()`. Jika tersedia, Arduino membaca data tersebut menggunakan `Serial.read()`.

Selanjutnya, Arduino melakukan pengecekan kondisi:

* Jika data = `'1'`, maka Arduino mengirimkan sinyal HIGH ke pin LED sehingga LED menyala
* Jika data = `'0'`, maka Arduino mengirimkan sinyal LOW sehingga LED mati

Dengan demikian, terjadi komunikasi dua arah antara komputer dan Arduino yang memungkinkan pengendalian LED secara real-time.

---

### 2. Fungsi Serial.available()

Fungsi `Serial.available()` digunakan untuk mengetahui apakah terdapat data yang masuk ke buffer serial.

Jika fungsi ini tidak digunakan:

* Arduino dapat mencoba membaca data meskipun belum ada data masuk
* Hal ini dapat menyebabkan pembacaan data tidak valid (garbage value)
* Program bisa menjadi tidak stabil atau menghasilkan output yang salah

Sehingga, fungsi ini penting untuk memastikan data benar-benar tersedia sebelum dibaca.

---

### 3. Modifikasi LED berkedip saat input '2'

Untuk membuat LED berkedip saat menerima input `'2'`, diperlukan penambahan kondisi pada program.

Saat karakter `'2'` diterima:

* Arduino masuk ke mode blinking
* LED akan menyala dan mati secara bergantian dalam loop
* Proses ini berlangsung terus sampai ada input baru yang menggantikan kondisi tersebut

Implementasi dapat menggunakan:

* `delay()` → sederhana tetapi blocking
* `millis()` → lebih baik karena tidak menghambat proses lain

---

### 4. delay() vs millis()

| Aspek          | delay()                        | millis()                   |
| -------------- | ------------------------------ | -------------------------- |
| Cara kerja     | Menghentikan program sementara | Tidak menghentikan program |
| Respons sistem | Lambat                         | Cepat/responsif            |
| Multi-tasking  | Tidak bisa                     | Bisa                       |
| Kelebihan      | Mudah digunakan                | Lebih efisien              |

**Kesimpulan:**
Penggunaan `millis()` lebih disarankan karena memungkinkan sistem tetap membaca input lain tanpa terhenti.

---

# 🔹 Percobaan 3B - I2C

## Dokumentasi Rangkaian
<img width="720" height="1280" alt="percobaan 2 (3)" src="https://github.com/user-attachments/assets/cec65c5f-18df-424e-977c-567085073205" />


## Jawaban Pertanyaan

### 1. Cara kerja komunikasi I2C antara Arduino dan LCD

Pada komunikasi I2C, Arduino berperan sebagai **master**, sedangkan LCD sebagai **slave**.

Komunikasi dilakukan melalui dua jalur:

* **SDA (Serial Data)** → untuk mengirim data
* **SCL (Serial Clock)** → untuk sinkronisasi

Setiap perangkat memiliki alamat unik (misalnya 0x27). Arduino mengirimkan data ke alamat tersebut, kemudian LCD menerima dan menampilkan data ke layar.

Keunggulan sistem ini adalah hanya menggunakan dua kabel meskipun dapat menghubungkan banyak perangkat.

---

### 2. Apakah pin potensiometer harus seperti itu?

Ya, susunan pin potensiometer harus sesuai:

* Kiri → GND
* Tengah → A0 (input ADC)
* Kanan → 5V

Jika pin kiri dan kanan tertukar:

* Tegangan yang masuk ke pin tengah tetap berubah, tetapi arah perubahan menjadi terbalik
* Saat diputar ke kanan, nilai ADC justru menurun

Hal ini tidak merusak rangkaian, tetapi membuat pembacaan menjadi tidak sesuai ekspektasi.

---

### 3. Penggabungan UART dan I2C dalam satu sistem

Pada sistem ini:

* UART digunakan sebagai **input** (dari Serial Monitor)
* I2C digunakan sebagai **output** (ke LCD)

Alur kerja:

1. Arduino menerima data dari komputer melalui UART
2. Data diproses di dalam program
3. Hasilnya ditampilkan ke LCD melalui I2C

Arduino dapat menjalankan kedua protokol ini secara bersamaan karena program berjalan secara berurutan dalam fungsi `loop()`.

---

### 4. Tabel Hasil Pengamatan

| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 5%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |

---

# 🔹 Pertanyaan Analisis

### 1. Keuntungan dan Kerugian UART dan I2C

**UART**

* ✔️ Mudah digunakan dan sederhana
* ✔️ Tidak memerlukan clock
* ❌ Hanya mendukung komunikasi point-to-point
* ❌ Kecepatan relatif terbatas

**I2C**

* ✔️ Hanya membutuhkan 2 kabel
* ✔️ Dapat menghubungkan banyak perangkat
* ❌ Lebih lambat dibanding SPI
* ❌ Memerlukan pengaturan alamat

---

### 2. Peran alamat I2C

Alamat I2C berfungsi sebagai identitas unik setiap perangkat dalam satu jalur komunikasi.

Contoh:

* LCD bisa menggunakan alamat **0x27 atau 0x20**

Tanpa alamat ini, Arduino tidak dapat menentukan perangkat mana yang harus menerima data.

---

### 3. Alur kerja UART dan I2C dalam satu sistem

Dalam satu sistem:

1. Data masuk dari Serial Monitor melalui UART
2. Arduino membaca dan memproses data
3. Data hasil diproses dikirim ke LCD melalui I2C

Arduino mengatur kedua proses ini secara bergantian dalam loop sehingga tidak terjadi konflik.


# Kesimpulan

UART dan I2C merupakan protokol komunikasi penting dalam sistem tertanam. UART digunakan untuk komunikasi sederhana antara Arduino dan komputer, sedangkan I2C digunakan untuk komunikasi antar perangkat dengan efisiensi kabel. Kedua protokol dapat digunakan secara bersamaan dalam satu sistem untuk menghasilkan sistem yang lebih interaktif dan efisien.
