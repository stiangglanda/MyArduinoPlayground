#include "SPI.h"

volatile byte Empfangswert;

void setup() {
  pinMode(9, OUTPUT);
  SPCR |= bit (SPE);
  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();
}

void loop() {
  analogWrite(9, Empfangswert);
}

ISR (SPI_STC_vect)
{
  Empfangswert = SPDR; 
}  
