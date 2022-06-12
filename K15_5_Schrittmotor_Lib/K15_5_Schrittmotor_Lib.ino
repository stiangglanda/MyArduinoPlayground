#include "Schrittmotor.h"

Schrittmotor Zeiger1(9,10,11,12); 
Schrittmotor Zeiger2(4,5,6,7);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Zeiger1.Schleife();
  Zeiger2.Schleife();

  if (Serial.available() > 0) {
    char Eingabe = Serial.read();
    switch(Eingabe)
    {
      case 'r':
        Zeiger1.bewegeGeschwindigkeit(10);
      break;
      case 'R':
        Zeiger2.bewegeGeschwindigkeit(10);
      break;
      case 'l':
        Zeiger1.bewegeGeschwindigkeit(-10);
      break;
      case 'L':
        Zeiger2.bewegeGeschwindigkeit(-10);
      break;
      case 's':
        Zeiger1.Stopp();
        Zeiger2.Stopp();
      break;
      case 't':
        Zeiger1.bewegeGeschwindigkeit(1);
        Zeiger2.bewegeGeschwindigkeit(-1);
      break;
      case '0':
        Zeiger1.bewegePosition(0);
        Zeiger2.bewegePosition(0);
      break;
      
      case 'p':
        Serial.print("aktuelle Position Zeiger 1: ");
        Serial.println(Zeiger1.gibPosition());
        Serial.print("aktuelle Position Zeiger 2: ");
        Serial.println(Zeiger2.gibPosition());
      break;
    }
  }
}
