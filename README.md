Nama : Finda Wulan Febrianti
NIM : H1H024055

## 1.5 Pertanyaan Praktikum Percobaan 1A (Percabangan)

1. Pada kondisi apa program masuk ke blok if?
   Program masuk ke blok if ketika nilai variabel `timeDelay <= 100`. Artinya LED sudah berkedip sangat cepat karena delay telah berkurang dari nilai awal 1000 ms hingga mencapai 100 ms atau kurang. Pada kondisi ini program akan menjalankan jeda selama 3 detik kemudian mereset nilai `timeDelay` kembali ke 1000 ms.

2. Pada kondisi apa program masuk ke blok else?
   Program masuk ke blok else ketika nilai `timeDelay > 100`. Selama kondisi ini terpenuhi, program akan mengurangi nilai `timeDelay` sebesar 100 ms pada setiap siklus sehingga LED semakin cepat berkedip.

3. Apa fungsi dari perintah delay(timeDelay)?
   Perintah `delay(timeDelay)` berfungsi untuk menghentikan eksekusi program sementara selama waktu tertentu dalam satuan milidetik. Perintah ini digunakan saat LED menyala dan mati sehingga menentukan kecepatan kedip LED.

4. Modifikasi program (cepat → sedang → mati)
   Program dimodifikasi dengan menambahkan fase transisi. Setelah LED mencapai kecepatan maksimum, program tidak langsung reset tetapi masuk ke kondisi sedang (misalnya delay 500 ms) sebelum kembali ke kondisi awal.

---

## 1.6 Pertanyaan Praktikum Percobaan 2A (Perulangan)

1. Gambarkan rangkaian schematic
   Rangkaian terdiri dari enam buah LED yang masing-masing dihubungkan ke pin digital 2 hingga 7 melalui resistor 220Ω, dan kaki katoda dihubungkan ke GND.
  ![gambar rangkaian](https://github.com/user-attachments/assets/f080f0a6-8c8b-4e93-92c0-4d919d789b05)



3. Jelaskan bagaimana LED berjalan dari kiri ke kanan
   LED berjalan dari kiri ke kanan menggunakan perulangan for dengan variabel `ledPin` dimulai dari 2 hingga 7 (`ledPin++`). Setiap LED menyala selama 100 ms kemudian mati sebelum LED berikutnya menyala.

4. Jelaskan bagaimana LED kembali dari kanan ke kiri
   LED kembali dari kanan ke kiri menggunakan perulangan for kedua dengan variabel `ledPin` dari 7 ke 2 (`ledPin--`), sehingga urutan LED menjadi terbalik.

5. Program LED 3 kanan dan 3 kiri bergantian
   Program dibuat dengan membagi LED menjadi dua kelompok, yaitu kiri (pin 2–4) dan kanan (pin 5–7). Kedua kelompok dinyalakan secara bergantian menggunakan perulangan for sehingga menghasilkan efek nyala bergantian.

---

## 1.7 Pertanyaan Analisis

1. Uraikan hasil praktikum
   Percobaan 1A menunjukkan bahwa percabangan if-else dapat mengatur perubahan kecepatan LED secara bertahap dari lambat ke cepat lalu kembali ke kondisi awal. Percobaan 2A menunjukkan bahwa perulangan for dapat mengontrol beberapa LED secara berurutan sehingga menghasilkan efek running light.

2. Pengaruh perulangan terhadap program
   Perulangan membuat program lebih efisien karena mengurangi penulisan kode berulang dan mempermudah pengelolaan banyak LED.

3. Cara kerja percabangan
   Percabangan bekerja dengan mengevaluasi nilai `timeDelay`. Jika sudah mencapai batas tertentu maka program reset, jika belum maka delay terus dikurangi.

4. Kombinasi perulangan dan percabangan
   Kombinasi keduanya membuat sistem lebih dinamis dan responsif. Perulangan menjalankan proses berulang, sedangkan percabangan menentukan aksi berdasarkan kondisi.
