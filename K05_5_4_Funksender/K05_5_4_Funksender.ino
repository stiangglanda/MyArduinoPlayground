#include "RCSwitch.h"

RCSwitch Sendemodul = RCSwitch();

void setup() {
  Sendemodul.enableTransmit(10);
}

void loop() {
  Sendemodul.send(analogRead(2)+1, 16);
  delay(1000);  
}
