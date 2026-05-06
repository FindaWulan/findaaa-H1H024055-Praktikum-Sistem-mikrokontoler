##Percobaan 4A – ADC Kendali Servo##
<img width="1200" height="1600" alt="Dokumentasi percobaan A" src="https://github.com/user-attachments/assets/0dcb89e8-28d1-40f1-bf41-7a05242e19c3" />

1. Apa fungsi analogRead() pada praktikum ini?

Fungsi analogRead() digunakan untuk membaca nilai tegangan analog dari potensiometer melalui pin A0. Nilai tersebut kemudian dikonversi menjadi data digital dengan rentang 0–1023 menggunakan ADC pada Arduino.

2. Mengapa diperlukan fungsi map()?

Karena nilai ADC dan sudut servo memiliki rentang yang berbeda. ADC memiliki rentang 0–1023, sedangkan servo bergerak pada rentang 0°–180°. Fungsi map() digunakan untuk menyesuaikan kedua rentang tersebut.

Contoh:

pos = map(val, 0, 1023, 0, 180);
3. Bagaimana cara membatasi servo hanya bergerak 30°–150°?

Rentang sudut pada fungsi map() diubah menjadi 30 hingga 150.

Contoh:

pos = map(val, 0, 1023, 30, 150);

Dengan demikian servo hanya bergerak dari 30° sampai 150°.

##Percobaan 4B – PWM Kendali Kecerahan LED##
<img width="1200" height="1600" alt="Dokumentasi Percobaan B" src="https://github.com/user-attachments/assets/9a5b4794-3893-476b-8df9-c6cc3ced737c" />

1. Mengapa LED dapat diatur kecerahannya menggunakan analogWrite()?

Karena analogWrite() menghasilkan sinyal PWM yang mengatur duty cycle HIGH dan LOW secara cepat. Semakin besar nilai PWM, maka LED terlihat semakin terang.

Contoh:

analogWrite(ledPin, pwmValue);
2. Apa hubungan antara ADC dan PWM?

ADC memiliki rentang nilai 0–1023, sedangkan PWM memiliki rentang 0–255. Oleh karena itu diperlukan fungsi map() untuk mengubah nilai ADC menjadi nilai PWM.

Contoh:

pwmValue = map(adcValue, 0, 1023, 0, 255);
3. Bagaimana agar LED hanya menyala pada PWM 50–200?

Dapat menggunakan kondisi if.

Contoh:

if (pwmValue >= 50 && pwmValue <= 200) {
  analogWrite(ledPin, pwmValue);
} else {
  analogWrite(ledPin, 0);
}

Dengan kondisi tersebut LED hanya menyala ketika nilai PWM berada pada rentang 50–200.
