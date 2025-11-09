#include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// // Inisialisasi LCD I2C (alamat 0x27, 16 kolom, 2 baris)
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// // Pin definitions
// const int buttonPin = 2;      // Push button
// const int buzzerPin = 8;      // Buzzer aktif
// const int relayPin = 7;       // Relay module

// // Variables
// int countdown = 10;
// bool isCountingDown = false;
// unsigned long lastBeepTime = 0;
// int beepInterval = 1000;  // Interval beep dalam ms
// bool buttonPressed = false;

// void setup() {
//   // Setup pins
//   pinMode(buttonPin, INPUT_PULLUP);  // Menggunakan internal pull-up resistor
//   pinMode(buzzerPin, OUTPUT);
//   pinMode(relayPin, OUTPUT);
  
//   // Pastikan relay mati di awal
//   digitalWrite(relayPin, LOW);
  
//   // Inisialisasi LCD
//   lcd.init();
//   lcd.backlight();
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Tekan Tombol");
//   lcd.setCursor(0, 1);
//   lcd.print("Untuk Mulai");
  
//   Serial.begin(9600);
// }

// void loop() {
//   // Baca status tombol (LOW = ditekan karena pull-up)
//   if (digitalRead(buttonPin) == LOW && !isCountingDown && !buttonPressed) {
//     buttonPressed = true;
//     isCountingDown = true;
//     countdown = 10;
//     lcd.clear();
//     delay(50);  // Debounce
//   }
  
//   // Reset flag tombol saat dilepas
//   if (digitalRead(buttonPin) == HIGH) {
//     buttonPressed = false;
//   }
  
//   // Proses countdown
//   if (isCountingDown) {
//     unsigned long currentTime = millis();
    
//     // Tampilkan countdown di LCD
//     lcd.setCursor(0, 0);
//     lcd.print("Countdown:");
//     lcd.setCursor(0, 1);
//     lcd.print("    ");
//     lcd.setCursor(0, 1);
//     lcd.print(countdown);
//     lcd.print(" detik    ");
    
//     // Atur kecepatan beep berdasarkan countdown
//     if (countdown > 3) {
//       beepInterval = 1000;  // 1 detik
//     } else if (countdown == 3) {
//       beepInterval = 500;   // 0.5 detik
//     } else if (countdown == 2) {
//       beepInterval = 300;   // 0.3 detik
//     } else if (countdown == 1) {
//       beepInterval = 200;   // 0.2 detik
//     }
    
//     // Beep buzzer
//     if (currentTime - lastBeepTime >= beepInterval) {
//       digitalWrite(buzzerPin, HIGH);
//       delay(100);  // Durasi beep
//       digitalWrite(buzzerPin, LOW);
      
//       countdown--;
//       lastBeepTime = currentTime;
      
//       // Jika countdown mencapai 0
//       if (countdown < 0) {
//         // Tampilkan "BOOM!"
//         lcd.clear();
//         lcd.setCursor(4, 0);
//         lcd.print("BOOM!");
        
//         // Bunyi panjang
//         digitalWrite(buzzerPin, HIGH);
//         delay(500);
//         digitalWrite(buzzerPin, LOW);
        
//         // AKTIFKAN RELAY (UNTUK SIMULASI SAJA!)
//         // GANTI dengan LED atau indikator aman lainnya
//         digitalWrite(relayPin, HIGH);
        
//         Serial.println("RELAY AKTIF - GUNAKAN UNTUK LED/INDIKATOR AMAN!");
        
//         delay(3000);  // Tampilkan "BOOM!" selama 3 detik
        
//         // Reset
//         digitalWrite(relayPin, LOW);
//         isCountingDown = false;
//         countdown = 10;
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("Tekan Tombol");
//         lcd.setCursor(0, 1);
//         lcd.print("Untuk Mulai");
//       }
//     }
//   }
// }

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD I2C (alamat 0x27, 16 kolom, 2 baris)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int switchPin = 2;      // Toggle Switch
const int buzzerPin = 8;      // Buzzer aktif (untuk tone)
const int relayPin = 7;       // Relay module

// Variables
int countdown = 10;
bool isCountingDown = false;
bool systemActive = false;
unsigned long lastBeepTime = 0;
int beepInterval = 1000;  // Interval beep dalam ms
int beepFrequency = 1000; // Frekuensi tone buzzer dalam Hz

void setup() {
  // Setup pins
  pinMode(switchPin, INPUT_PULLUP);  // Menggunakan internal pull-up resistor
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  // Pastikan relay mati di awal
  digitalWrite(relayPin, LOW);
  
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Switch OFF");
  lcd.setCursor(0, 1);
  lcd.print("Standby Mode");
  
  Serial.begin(9600);
}

void loop() {
  // Baca status switch (LOW = ON karena pull-up)
  bool switchState = (digitalRead(switchPin) == LOW);
  
  // Jika switch ON dan sistem belum aktif
  if (switchState && !systemActive) {
    systemActive = true;
    isCountingDown = true;
    countdown = 10;
    lcd.clear();
    delay(100);
    Serial.println("Switch ON - Program dimulai!");
  }
  
  // Jika switch OFF, reset sistem
  if (!switchState && systemActive) {
    systemActive = false;
    isCountingDown = false;
    countdown = 10;
    digitalWrite(relayPin, LOW);
    noTone(buzzerPin);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Switch OFF");
    lcd.setCursor(0, 1);
    lcd.print("Standby Mode");
    Serial.println("Switch OFF - Sistem di-reset");
  }
  
  // Proses countdown jika sistem aktif
  if (isCountingDown && systemActive) {
    unsigned long currentTime = millis();
    
    // Tampilkan countdown di LCD
    lcd.setCursor(0, 0);
    lcd.print("Countdown:");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(countdown);
    lcd.print(" detik    ");
    
    // Atur kecepatan beep dan frekuensi berdasarkan countdown
    if (countdown > 3) {
      beepInterval = 1000;   // 1 detik
      beepFrequency = 1000;  // 1000 Hz (nada rendah)
    } else if (countdown == 3) {
      beepInterval = 500;    // 0.5 detik
      beepFrequency = 1500;  // 1500 Hz (nada sedang)
    } else if (countdown == 2) {
      beepInterval = 300;    // 0.3 detik
      beepFrequency = 2000;  // 2000 Hz (nada tinggi)
    } else if (countdown == 1) {
      beepInterval = 200;    // 0.2 detik
      beepFrequency = 2500;  // 2500 Hz (nada sangat tinggi)
    }
    
    // Beep buzzer dengan tone
    if (currentTime - lastBeepTime >= beepInterval) {
      // Bunyi beep dengan tone
      tone(buzzerPin, beepFrequency, 100);  // Bunyi selama 100ms
      
      Serial.print("Countdown: ");
      Serial.print(countdown);
      Serial.print(" - Tone: ");
      Serial.print(beepFrequency);
      Serial.println(" Hz");
      
      countdown--;
      lastBeepTime = currentTime;
      
      // Jika countdown mencapai 0
      if (countdown < 0) {
        // Tampilkan "BOOM!"
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("BOOM!");
        
        // Bunyi panjang dengan tone tinggi (alarm)
        tone(buzzerPin, 3000, 200);  // 3000 Hz selama 200ms
        delay(250);
        tone(buzzerPin, 2500, 200);  // 2500 Hz selama 200ms
        delay(250);
        tone(buzzerPin, 3500, 300);  // 3500 Hz selama 300ms
        
        // AKTIFKAN RELAY - Power Supply 19V akan mengalir
        digitalWrite(relayPin, HIGH);
        
        Serial.println("BOOM! RELAY AKTIF - POWER SUPPLY 19V MENGALIR KE BEBAN!");
        
        delay(5000);  // Tampilkan "BOOM!" dan biarkan relay aktif selama 5 detik
        
        // MATIKAN RELAY setelah 5 detik
        digitalWrite(relayPin, LOW);
        Serial.println("RELAY MATI - Power supply terputus");
        
        // Reset countdown
        isCountingDown = false;
        countdown = 10;
        
        // Tampilkan status selesai
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Selesai!");
        lcd.setCursor(0, 1);
        lcd.print("Matikan Switch");
        
        delay(2000);
        
        // Jika switch masih ON, mulai lagi
        if (digitalRead(switchPin) == LOW) {
          isCountingDown = true;
          countdown = 10;
          lcd.clear();
        }
      }
    }
  }
}