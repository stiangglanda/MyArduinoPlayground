#include "IRremote.h"

int RECV_PIN = 2; 

IRrecv Empfaenger(RECV_PIN);
decode_results Daten;

void setup()
{
  Serial.begin(9600);
  Empfaenger.enableIRIn(); 
}

void loop() {
  if (Empfaenger.decode(&Daten)) {
    Serial.print("Empfangene Daten: ");
    Serial.println(Daten.value, HEX);
    Empfaenger.resume();
  }
}
