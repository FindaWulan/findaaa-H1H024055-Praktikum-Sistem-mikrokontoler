# Modul V – Real-Time Operating System (RTOS)

**Nama:** Finda Wulan Febrianti  
**NIM:** H1H024055  
**Asisten:** Arga Aryanta Indrafata  

## Deskripsi

Praktikum ini mengimplementasikan **FreeRTOS** pada Arduino Uno untuk dua skenario:

- **Percobaan 5A** – Multitasking dengan 3 task concurrent menggunakan `xTaskCreate()` dan `vTaskDelay()`
- **Percobaan 5B** – Komunikasi antar-task menggunakan message queue (`xQueueCreate`, `xQueueSend`, `xQueueReceive`)

---

## Alat dan Bahan

| Komponen | Jumlah |
|----------|--------|
| Arduino Uno | 1 |
| LED Merah | 1 |
| LED Kuning | 1 |
| Resistor 220Ω | 2 |
| Breadboard | 1 |
| Kabel Jumper | Secukupnya |
| Sensor DHT (5B) | 1 |
| Komputer + Arduino IDE | 1 |

Library yang dibutuhkan: **Arduino_FreeRTOS**

---

## Percobaan 5A – Multitasking

### Skema Rangkaian

- LED Merah → Pin **D8** → Resistor 220Ω → GND
- LED Kuning → Pin **D10** → Resistor 220Ω → GND

### Kode Program

```cpp
#include <Arduino_FreeRTOS.h>

// Deklarasi prototipe task
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void Taskprint(void *pvParameters);

void setup() {
  Serial.begin(9600);  // Inisialisasi komunikasi serial 9600 baud

  // Membuat task TaskBlink1: LED merah, stack 128 word, prioritas 1
  xTaskCreate(TaskBlink1, "Blink1", 128, NULL, 1, NULL);

  // Membuat task TaskBlink2: LED kuning, stack 128 word, prioritas 1
  xTaskCreate(TaskBlink2, "Blink2", 128, NULL, 1, NULL);

  // Membuat task Taskprint: counter serial, stack 128 word, prioritas 1
  xTaskCreate(Taskprint, "Print", 128, NULL, 1, NULL);

  // vTaskStartScheduler() dipanggil otomatis oleh FreeRTOS setelah setup()
}

void loop() {
  // Dikosongkan: setelah scheduler aktif, loop() tidak digunakan
  // Semua eksekusi dikelola oleh FreeRTOS scheduler
}

// Task 1: Mengedipkan LED Merah setiap 200ms
void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);           // Set pin D8 sebagai output
  for (;;) {                    // Loop tak terbatas (pengganti loop() dalam task)
    digitalWrite(8, HIGH);      // Nyalakan LED merah
    vTaskDelay(200 / portTICK_PERIOD_MS);  // Tunggu 200ms (non-blocking)
    digitalWrite(8, LOW);       // Matikan LED merah
    vTaskDelay(200 / portTICK_PERIOD_MS);  // Tunggu 200ms (non-blocking)
  }
}

// Task 2: Mengedipkan LED Kuning setiap 300ms
void TaskBlink2(void *pvParameters) {
  pinMode(10, OUTPUT);          // Set pin D10 sebagai output
  for (;;) {
    digitalWrite(10, HIGH);     // Nyalakan LED kuning
    vTaskDelay(300 / portTICK_PERIOD_MS);  // Tunggu 300ms
    digitalWrite(10, LOW);      // Matikan LED kuning
    vTaskDelay(300 / portTICK_PERIOD_MS);  // Tunggu 300ms
  }
}

// Task 3: Menampilkan counter ke Serial Monitor setiap 500ms
void Taskprint(void *pvParameters) {
  int counter = 0;              // Inisialisasi counter
  for (;;) {
    Serial.print("Counter: ");  // Cetak label ke Serial Monitor
    Serial.println(counter++);  // Cetak nilai counter lalu increment
    vTaskDelay(500 / portTICK_PERIOD_MS);  // Tunggu 500ms
  }
}
```

### Penjelasan Tiap Baris Penting

| Baris / Fungsi | Penjelasan |
|----------------|------------|
| `#include <Arduino_FreeRTOS.h>` | Menyertakan library FreeRTOS untuk Arduino |
| `xTaskCreate(func, nama, stack, param, prioritas, handle)` | Mendaftarkan task ke scheduler FreeRTOS. Stack 128 words, prioritas 1 |
| `vTaskDelay(ms / portTICK_PERIOD_MS)` | Menghentikan task sementara (state Blocked) tanpa memblokir CPU; task lain tetap berjalan |
| `for (;;)` | Loop tak terbatas di dalam task, menggantikan peran `loop()` |
| `loop()` kosong | Setelah `vTaskStartScheduler()` aktif, `loop()` tidak dibutuhkan dan sebaiknya dikosongkan |

### Modifikasi dengan Potensiometer

Task keempat `TaskPot` ditambahkan untuk membaca nilai ADC dari potensiometer di pin `A0` setiap 100ms, lalu memetakannya ke delay LED menggunakan `map()`:

```cpp
void TaskPot(void *pvParameters) {
  for (;;) {
    int adcVal = analogRead(A0);                      // Baca nilai ADC (0–1023)
    int delayMs = map(adcVal, 0, 1023, 50, 1000);    // Petakan ke 50–1000ms
    digitalWrite(8, HIGH);
    vTaskDelay(delayMs / portTICK_PERIOD_MS);
    digitalWrite(8, LOW);
    vTaskDelay(delayMs / portTICK_PERIOD_MS);
  }
}
```

Nilai ADC besar → delay kecil (kedip cepat); nilai ADC kecil → delay besar (kedip lambat).

---

## Percobaan 5B – Komunikasi Task (Message Queue)

### Skema

Hanya menggunakan Arduino Uno dan Serial Monitor (tidak ada komponen eksternal tambahan selain kabel USB).

### Kode Program

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Definisi struct untuk data yang dikirim via queue
struct readings {
  int temp;   // Data suhu
  int h;      // Data kelembaban
};

QueueHandle_t dataQueue;  // Handle queue global

void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {
  Serial.begin(9600);

  // Membuat queue berkapasitas 1 item bertipe struct readings
  dataQueue = xQueueCreate(1, sizeof(struct readings));

  // Membuat task pengirim data (sensor simulasi)
  xTaskCreate(read_data, "ReadData", 128, NULL, 1, NULL);

  // Membuat task penerima & penampil data
  xTaskCreate(display, "Display", 128, NULL, 1, NULL);
}

void loop() {
  // Kosong: dikelola scheduler
}

// Task pengirim: simulasi data sensor, kirim ke queue setiap 100ms
void read_data(void *pvParameters) {
  struct readings sensorData;  // Buat instance struct
  for (;;) {
    sensorData.temp = 54;      // Nilai suhu statis (simulasi)
    sensorData.h = 30;         // Nilai kelembaban statis (simulasi)

    // Kirim struct ke queue; tunggu selamanya jika queue penuh (portMAX_DELAY)
    xQueueSend(dataQueue, &sensorData, portMAX_DELAY);

    vTaskDelay(100 / portTICK_PERIOD_MS);  // Tunggu 100ms sebelum kirim lagi
  }
}

// Task penerima: tunggu data dari queue lalu tampilkan ke Serial Monitor
void display(void *pvParameters) {
  struct readings received;    // Struct untuk menampung data yang diterima
  for (;;) {
    // Tunggu data dari queue; task Blocked sampai data tersedia
    if (xQueueReceive(dataQueue, &received, portMAX_DELAY) == pdPASS) {
      Serial.print("temp = ");
      Serial.println(received.temp);   // Cetak suhu
      Serial.print("humidity = ");
      Serial.println(received.h);      // Cetak kelembaban
    }
  }
}
```

### Penjelasan Tiap Baris Penting

| Baris / Fungsi | Penjelasan |
|----------------|------------|
| `struct readings` | Struktur data yang membungkus suhu dan kelembaban menjadi satu paket |
| `xQueueCreate(1, sizeof(struct readings))` | Membuat queue dengan kapasitas 1 item; ukuran item = ukuran struct |
| `xQueueSend(queue, &data, portMAX_DELAY)` | Mengirim data ke queue; jika penuh, task menunggu tanpa batas |
| `xQueueReceive(queue, &buffer, portMAX_DELAY)` | Menerima data dari queue; jika kosong, task Blocked sampai ada data |
| `portMAX_DELAY` | Konstanta FreeRTOS untuk menunggu tanpa batas waktu (blocking) |
| `pdPASS` | Nilai return yang menandakan operasi queue berhasil |

### Modifikasi dengan Sensor DHT Sesungguhnya

```cpp
#include <DHT.h>

#define DHTPIN 7        // Pin data sensor DHT
#define DHTTYPE DHT11   // Tipe sensor: DHT11

DHT dht(DHTPIN, DHTTYPE);  // Inisialisasi objek DHT

void read_data(void *pvParameters) {
  struct readings sensorData;
  dht.begin();               // Mulai sensor
  for (;;) {
    sensorData.temp = (int)dht.readTemperature();  // Baca suhu nyata (°C)
    sensorData.h    = (int)dht.readHumidity();     // Baca kelembaban nyata (%)
    xQueueSend(dataQueue, &sensorData, portMAX_DELAY);
    vTaskDelay(2000 / portTICK_PERIOD_MS);  // DHT11 butuh min. 2s antar pembacaan
  }
}
```

Data suhu dan kelembaban kini bersifat dinamis sesuai kondisi lingkungan.

---

## Hasil Percobaan

| Percobaan | Parameter | Hasil |
|-----------|-----------|-------|
| 5A | Multitasking berjalan | 3 task concurrent tanpa konflik |
| 5A | Output Serial Monitor | Counter bertambah setiap 500ms |
| 5A | Scheduler FreeRTOS | Berfungsi, LED berkedip sesuai periode |
| 5B | Pengiriman data via queue | Data struct terkirim dan diterima tanpa error |
| 5B | Output Serial Monitor | Nilai temp dan humidity tampil berulang |
