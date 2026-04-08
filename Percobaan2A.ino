int timer = 100; // delay waktu (semakin besar semakin lambat)

void setup() {
  // Inisialisasi semua pin LED (2 - 7) sebagai output
  for (int ledPin = 2; ledPin < 8; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
}

void loop() {
  // LED menyala dari kiri ke kanan (pin 2 → 7)
  for (int ledPin = 2; ledPin < 8; ledPin++) {
    digitalWrite(ledPin, HIGH); // nyalakan LED
    delay(timer);               // tunggu
    digitalWrite(ledPin, LOW);  // matikan LED
  }

  // LED menyala dari kanan ke kiri (pin 7 → 2)
  for (int ledPin = 7; ledPin >= 2; ledPin--) {
    digitalWrite(ledPin, HIGH); // nyalakan LED
    delay(timer);               // tunggu
    digitalWrite(ledPin, LOW);  // matikan LED
  }
}