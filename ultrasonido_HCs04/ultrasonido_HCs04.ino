#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13); //    ( RS, EN, d4, d5, d6, d7) 

const int EchoPin = 9;
const int TriggerPin = 8;
const int LedPin = 13;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);       // Fijar el numero de caracteres y de filas de la LCD
  pinMode(LedPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {
  int cm = ping(TriggerPin, EchoPin);
  Serial.print("Distancia: ");
  Serial.println(cm);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(cm);

  delay(1000);
}

int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  
  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  
  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
  return distanceCm;
}
