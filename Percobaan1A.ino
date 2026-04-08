const int ledPin = 6;     // Pin LED di pin 6
int timeDelay = 1000;     // Delay awal (1000 ms = 1 detik)

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin sebagai output
}

void loop() {
  // LED menyala
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);

  // LED mati
  digitalWrite(ledPin, LOW);
  delay(timeDelay);

  // Percabangan untuk mengatur kecepatan
  if (timeDelay <= 100) {
    delay(3000);          // Jeda sebelum reset
    timeDelay = 1000;     // Kembali ke awal
  } else {
    timeDelay -= 100;     // Percepat kedipan LED
  }
}