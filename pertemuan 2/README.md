# 📘 README – Pertanyaan Analisis (4.3)

## Identitas
- Nama: Finda Wulan Febrianti  
- NIM: H1H024055  

---

##  4.3 Pertanyaan Analisis

### 1. Analisis hasil percobaan 2A dan 2B
Hasil percobaan 2A menunjukkan bahwa seven segment berhasil difungsikan sebagai counter heksadesimal otomatis yang menampilkan 0–F secara berurutan menggunakan pola bit dalam array dua dimensi.  

Percobaan 2B menunjukkan bahwa push button dapat digunakan sebagai input digital yang andal untuk mengendalikan nilai counter secara manual dengan bantuan mekanisme edge detection.

---

### 2. Prinsip kerja seven segment
Seven segment bekerja berdasarkan kombinasi segmen LED yang dinyalakan untuk membentuk karakter tertentu.  

Setiap karakter memiliki pola unik, contohnya:
- Angka **0** → segmen a, b, c, d, e, f menyala (g mati)  
- Huruf **A** → segmen a, b, c, e, f, g menyala (d mati)  

Arduino mengatur nyala/mati segmen dengan memberikan logika **HIGH atau LOW** pada setiap pin sesuai pola yang telah diprogram.

---

### 3. Cara kerja sistem counter
Sistem counter bekerja menggunakan variabel `currentDigit` yang nilainya:
- Bertambah otomatis (percobaan 2A)  
- Bertambah saat tombol ditekan (percobaan 2B)  

Nilai ini digunakan sebagai indeks untuk mengambil data dari array `digitPattern`, lalu dikirim ke seven segment melalui fungsi `displayDigit()`.  

Jika nilai melebihi 15, maka counter akan otomatis kembali ke 0.

---

## Kesimpulan Singkat
- Seven segment menampilkan karakter berdasarkan pola bit  
- Counter dikontrol oleh variabel dan input  
- Push button memungkinkan kontrol manual  
- Sistem berjalan otomatis maupun interaktif  

---

✨ *Disusun berdasarkan hasil praktikum Modul II GPIO*