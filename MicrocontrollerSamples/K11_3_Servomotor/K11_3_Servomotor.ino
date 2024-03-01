#define SERVOPIN 10
#define SENSORPIN 3

#include "Servo.h"

Servo Servomotor;

int Sensorwert;
byte Servowinkel;

void setup() {
  Servomotor.attach(SERVOPIN);
}

void loop() {
  Sensorwert = analogRead(SENSORPIN);
  Servowinkel = map(Sensorwert, 0, 1023, 0, 180);
  Servomotor.write(Servowinkel);
  delay(50);
}
