#include <SPI.h>

void setup() {
  digitalWrite(SS, HIGH);
  SPI.begin();  
}

int Drehregler = 0;

void loop() {
  Drehregler = analogRead(2);
  Drehregler /= 4;
  digitalWrite(SS, LOW);   
  SPI.transfer (Drehregler);
  digitalWrite(SS, HIGH);
  delay(500);
}
