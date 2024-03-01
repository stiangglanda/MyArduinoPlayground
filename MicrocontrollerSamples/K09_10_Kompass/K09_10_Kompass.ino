#include "Wire.h"
#include "MechaQMC5883.h"

MechaQMC5883 Kompass;
int x, y, z;
int azimuth;
  
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Kompass.init();
}

void loop() {
  Kompass.read(&x, &y, &z,&azimuth);
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.print(z);
  Serial.print(" Azimuth: ");
  Serial.print(azimuth);
  Serial.println();
  delay(500);
}
