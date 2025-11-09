💣 Meletup-Project – Arduino Countdown Simulation
🧠 Deskripsi Umum

Meletup-Project adalah sebuah simulasi sistem penghitung waktu mundur (countdown timer) berbasis Arduino Uno, yang menggambarkan skenario sederhana “bom waktu”.
Ketika switch dinyalakan (ditekan ON), sistem akan memulai hitungan mundur selama 10 detik yang ditampilkan di LCD Display.
Setelah waktu mencapai nol, buzzer akan berbunyi dan layar akan menampilkan tulisan “BOOM!”.
Proyek ini merupakan simulasi edukatif untuk mempelajari penggunaan komponen input/output dasar Arduino seperti LCD, buzzer, LED, dan push button.

⚙️ Komponen yang Digunakan

Arduino Uno R3

LCD 16x2 (I2C)

Push Button (Switch)

Buzzer aktif

LED indikator

Resistor 220Ω

IC ULN2003A (Driver Transistor)

Breadboard

Kabel jumper

🔌 Penjelasan Skema Koneksi

(Gambar skematik sesuai file Meletup-project.JPG)

Push Button → Terhubung ke pin digital 2 Arduino sebagai input start.

Buzzer → Terhubung ke pin 8 Arduino.

LED → Terhubung ke pin 13 Arduino (menyala saat countdown aktif).

LCD 16x2 I2C →

SDA ke pin A4

SCL ke pin A5

VCC ke 5V

GND ke GND

IC ULN2003A → Sebagai driver untuk mengatur arus LED atau buzzer.

Ground dan VCC semua komponen disatukan di jalur breadboard.

💡 Cara Kerja Sistem

Saat switch ditekan ON, Arduino memulai hitungan mundur dari 10 detik.

LED akan menyala sebagai tanda sistem aktif.

Nilai waktu akan ditampilkan di LCD, misalnya:

Countdown: 10
Countdown: 9
...


Setelah mencapai nol, LCD akan menampilkan:

💥 BOOM! 💥


Buzzer berbunyi secara berulang sebagai tanda waktu habis.

LED dapat mati atau berkedip bersamaan dengan bunyi buzzer untuk efek dramatis.