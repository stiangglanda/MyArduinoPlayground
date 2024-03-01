#include "Wire.h"

byte Empfangswert;

void setup() {
  Wire.begin(8);            
  Wire.onReceive(Datenempfang); 
  pinMode(10, OUTPUT);
}

void loop() {
  analogWrite(10, Empfangswert);
}

void Datenempfang(int howMany) {
  if(Wire.available())
    Empfangswert = Wire.read();   
}
