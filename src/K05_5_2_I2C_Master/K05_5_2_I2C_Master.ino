#include "Wire.h"

void setup() {
  Wire.begin(); 
}

int Drehregler = 0;

void loop() {
  Drehregler = analogRead(2);
  Drehregler /= 4;
  Wire.beginTransmission(8); 
  Wire.write(Drehregler);
  Wire.endTransmission();
  
  delay(500);
}
