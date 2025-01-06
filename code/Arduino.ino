// Adım motoru kontrolü için kütüphane
#include <Stepper.h>

// Pin tanımlamaları
int xPin = A0; 
int yPin = A1; 
int butonPin = 2; 

// Değişken tanımlamaları
int xPozisyon;
int yPozisyon;
int butonDurum;

// Motorun adım sayısı
const int stepsPerRevolution = 80;

// Stepper nesnesi oluştur
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);  // Seri iletişim başlatılır
  pinMode(xPin, INPUT);  // X ekseninin analog okuması için pin ayarlanır
  pinMode(yPin, INPUT);  // Y ekseninin analog okuması için pin ayarlanır
  pinMode(butonPin, INPUT_PULLUP);  // Buton pin'i iç direnç ile INPUT_PULLUP modunda ayarlanır
}

void loop() {
  // Joystick değerleri ve buton durumu okunur
  xPozisyon = analogRead(xPin);
  yPozisyon = analogRead(yPin);
  butonDurum = digitalRead(butonPin);
  
  // Joystick değerleri ve buton durumu Serial Monitor üzerinden izlenir
  Serial.print("X Pozisyonu: ");
  Serial.print(xPozisyon);
  Serial.print(" | Y Pozisyonu: ");
  Serial.print(yPozisyon);
  Serial.print(" | Buton Durum: ");
  Serial.println(butonDurum);

  // X eksenindeki joystick hareketine bağlı olarak motoru belirli bir yönde hareket ettir
  if (xPozisyon > 1000) {
    myStepper.setSpeed(60);
    myStepper.step(5);
  }
  
  // Y eksenindeki joystick hareketine bağlı olarak motoru belirli bir yönde hareket ettir
  if (yPozisyon > 1000) {
    myStepper.setSpeed(30);
    myStepper.step(1);
  }

  // X eksenindeki joystick hareketine bağlı olarak motoru ters yönde hareket ettir
  if (xPozisyon < 50) {
    myStepper.setSpeed(60);
    myStepper.step(-5);
  }
  
  // Y eksenindeki joystick hareketine bağlı olarak motoru ters yönde hareket ettir
  if (yPozisyon < 50) {
    myStepper.setSpeed(30);
    myStepper.step(-1);
  }
   if (butonDurum == 0) {
    myStepper.setSpeed(30);
    myStepper.step(stepsPerRevolution);
    delay(1000); // 1 saniye bekle
    myStepper.step(-stepsPerRevolution);


  }

}