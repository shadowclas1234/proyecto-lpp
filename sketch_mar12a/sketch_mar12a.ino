#include <LiquidCrystal.h>

const int termistorPin = A0;
const int ledPin = 13;
const int motorBotellaPin = 6;  // Pin del motor que mueve la botella cortada
const int motorFilamentoPin = 7;  // Pin del motor que guía el filamento
const int motorAlmacenamientoPin = 8;  // Pin del motor que almacena el plástico en un rollo para filamento 3D
const int potPin = A1; // Pin del potenciómetro

const float R1 = 10000;  
const float R2 = 10000;  
const float Vin = 5.0;   

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(motorBotellaPin, OUTPUT);
  pinMode(motorFilamentoPin, OUTPUT);
  pinMode(motorAlmacenamientoPin, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("Temperatura:");
}

void loop() {

  int raw = analogRead(termistorPin);
  int potValue = analogRead(potPin); // Lee el valor del potenciómetro
  
  // Mapea el valor del potenciómetro a un rango de temperaturas entre 0 y 50 grados Celsius
  float tempThreshold = map(potValue, 0, 1023, 0, 50);
  
  float Rth = R1 * (1023.0 / raw - 1.0);
  
  float tempC = 1.0 / (1.0 / 298.15 + 1.0 / 3435.0 * log(Rth / R2)) - 273.15;
  
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print(" C");
  
  if (tempC > tempThreshold) { // Compara con el umbral de temperatura ajustado por el potenciómetro
    digitalWrite(ledPin, HIGH);
    // Encender motores para mover la botella, guiar el filamento y almacenar el plástico
    digitalWrite(motorBotellaPin, HIGH);
    digitalWrite(motorFilamentoPin, HIGH);
    digitalWrite(motorAlmacenamientoPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    // Apagar motores
    digitalWrite(motorBotellaPin, LOW);
    digitalWrite(motorFilamentoPin, LOW);
    digitalWrite(motorAlmacenamientoPin, LOW);
  }
  
  delay(1000);
}
