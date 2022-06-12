#include "RCSwitch.h"

RCSwitch Empfangsmodul = RCSwitch();

void setup() 
{
  Serial.begin(9600);
  Empfangsmodul.enableReceive(0); 
  pinMode(9, OUTPUT);
}

void loop() {
  if (Empfangsmodul.available()) 
  {
    int Empfangswert = Empfangsmodul.getReceivedValue(); 
    Serial.print("Empfangswert: ");
    Serial.println(Empfangswert);
    analogWrite(9, (Empfangswert-1)/4); 
  }
  Empfangsmodul.resetAvailable(); 
}
