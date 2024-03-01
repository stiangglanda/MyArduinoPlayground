#define KNOPF1 9
#define KNOPF2 8
#define LED 6

#include "uEEPROMLib.h"

uEEPROMLib externerSpeicher(87);

byte Helligkeit;
long Timer;

void setup() {
  pinMode(KNOPF1,INPUT_PULLUP);
  pinMode(KNOPF2,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  
  Wire.begin();
  Helligkeit = externerSpeicher.eeprom_read(0);
  
  analogWrite(LED, Helligkeit);
}

void loop() {
  if(!digitalRead(KNOPF1))
  {
    if(Helligkeit < 255)
      Helligkeit++;
    analogWrite(LED, Helligkeit);

    Timer = millis() + 1000;
    while(!digitalRead(KNOPF1))
    {
      if(millis() > Timer)
      {
        if(Helligkeit < 255)
          Helligkeit++;
        analogWrite(LED, Helligkeit);  
        delay(10);  
      }
    }
    externerSpeicher.eeprom_write(0,Helligkeit);
  }

  if(!digitalRead(KNOPF2))
  {
    if(Helligkeit > 0)
      Helligkeit--;
    analogWrite(LED, Helligkeit);

    Timer = millis() + 1000;
    while(!digitalRead(KNOPF2))
    {
      if(millis() > Timer)
      {
        if(Helligkeit > 0)
          Helligkeit--;
        analogWrite(LED, Helligkeit);  
        delay(10);  
      }
    }
    externerSpeicher.eeprom_write(0,Helligkeit);
  }
}
