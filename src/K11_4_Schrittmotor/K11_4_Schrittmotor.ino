#define SCHRITTEPROUMDREHUNG 2048

#include "Stepper.h"

Stepper Schrittmotor(SCHRITTEPROUMDREHUNG, 8, 10, 9, 11);

void setup() {
}

void loop() {
  Schrittmotor.setSpeed(5);
  Schrittmotor.step(SCHRITTEPROUMDREHUNG);
  delay(500);

  Schrittmotor.setSpeed(1);
  Schrittmotor.step(-SCHRITTEPROUMDREHUNG/4);
  delay(500);
}
