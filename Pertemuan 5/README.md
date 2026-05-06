4. HASIL DAN ANALISIS
4.1 Percobaan 4A – ADC Kendali Servo

Pada percobaan ini, servo berhasil bergerak mengikuti putaran potensiometer. Saat potensiometer diputar, nilai ADC berubah dan sudut servo ikut berubah dari 0° sampai 180°. Nilai ADC dan sudut servo juga tampil pada Serial Monitor.

Gambar 4.1 Dokumentasi Percobaan ADC Kendali Servo

[Masukkan Foto Percobaan Servo]

Analisis

Berdasarkan hasil percobaan, ADC berhasil membaca nilai analog dari potensiometer dan mengubahnya menjadi data digital. Nilai tersebut kemudian digunakan untuk mengontrol sudut servo menggunakan fungsi map().

4.2 Percobaan 4B – PWM Kendali Kecerahan LED

Pada percobaan ini, LED berhasil menyala dengan tingkat kecerahan yang berbeda sesuai putaran potensiometer. Semakin besar nilai ADC, maka LED semakin terang.


Gambar 4.2 Dokumentasi Percobaan PWM Kendali Kecerahan LED

Analisis

PWM berhasil digunakan untuk mengatur kecerahan LED menggunakan fungsi analogWrite(). Nilai ADC dari potensiometer diubah menjadi nilai PWM sehingga intensitas cahaya LED dapat berubah secara bertahap.