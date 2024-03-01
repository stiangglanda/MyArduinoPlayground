#include "Arduino.h"
#include "Schrittmotor.h"

Schrittmotor::Schrittmotor(byte a, byte b, byte c, byte d)       // Konstruktor
{
  p1 = a<14 ? a : 1;
  p2 = b<14 ? b : 2;
  p3 = b<14 ? c : 3;
  p4 = b<14 ? d : 4;
  Modus = 0;
  StartPosition = 0L; StartZeit = 0L;
  aktuellePosition = 0L; aktuelleGeschwindigkeit = 0L;
  ZielPosition = 0L; Timer = 0L;
  SchritteProUmdrehung = 2048;
  maxGeschwindigkeit = 15;
  pinMode(p1, OUTPUT); pinMode(p2, OUTPUT); pinMode(p3, OUTPUT); pinMode(p4, OUTPUT);
  Ausgabe(4);
}

void Schrittmotor::Ausgabe(char Phase)
{
 switch(Phase)
  { // Phasen 0-3 stellen die einzelnen Rotationsschritte dar.
    case 0:
      digitalWrite(p1,HIGH); digitalWrite(p2,HIGH); digitalWrite(p3,LOW); digitalWrite(p4,LOW);
    break;
    case 1: case -3:
      digitalWrite(p1,LOW); digitalWrite(p2,HIGH); digitalWrite(p3,HIGH); digitalWrite(p4,LOW);
    break;
    case 2: case -2:
      digitalWrite(p1,LOW); digitalWrite(p2,LOW); digitalWrite(p3,HIGH); digitalWrite(p4,HIGH);
    break;
    case 3: case -1:
      digitalWrite(p1,HIGH); digitalWrite(p2,LOW); digitalWrite(p3,LOW); digitalWrite(p4,HIGH);
    break;
    case 4: // Phase 4 ist vorgesehen, um alle Ausgänge auf LOW zu schalten (Stromsparen im Stillstand).
      digitalWrite(p1,LOW); digitalWrite(p2,LOW); digitalWrite(p3,LOW); digitalWrite(p4,LOW);
    break;
  }
  return true;
}


void Schrittmotor::bewegeGeschwindigkeit(int Geschwindigkeit)
{
  if(abs(Geschwindigkeit) > 0 && abs(Geschwindigkeit) <= maxGeschwindigkeit)
  {
    Modus = 1;
    aktuelleGeschwindigkeit = Geschwindigkeit;
    StartPosition = aktuellePosition;
    StartZeit = millis();
    return true;
  }
  else
    return false;
}

void Schrittmotor::bewegePosition(long Position)
{
  Modus = 2;
  ZielPosition = Position;
}


void Schrittmotor::Schleife(void)
{
  if(!Modus)
    Ausgabe(4);
  if(Modus == 1)
  {
    long Zeitdifferenz = millis() - StartZeit;
    aktuellePosition = StartPosition + (Zeitdifferenz * SchritteProUmdrehung * aktuelleGeschwindigkeit / 60000L);
    Ausgabe(aktuellePosition % 4); 
  }
  if(Modus == 2 && millis() > Timer)
  {
    if(ZielPosition > aktuellePosition)
      aktuellePosition++;
    if(ZielPosition < aktuellePosition)
      aktuellePosition--;
    if(ZielPosition == aktuellePosition)
      Modus = 0;
    Ausgabe(aktuellePosition%4); 
    Timer = millis() + 1;
  }
}