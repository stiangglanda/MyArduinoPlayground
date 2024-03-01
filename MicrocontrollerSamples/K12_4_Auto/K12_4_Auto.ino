#define MR_A    4  
#define MR_B    9
#define MR_PWM  5
#define ML_A   11
#define ML_B   12
#define ML_PWM 10
#define IR_PIN  2   // Pin des IR-Empfängers
#define ECHOPIN 7   // Pins des Ultraschallmoduls
#define TRIGPIN 8

#define ML 0        // symbolisiert linken Motor
#define MR 1        // symbolisiert rechten Motor
#define VOR 0
#define RUECK 1
#define STUFE1 128  // Leistungsstufen
#define STUFE2 255

#include "IRremote.h"
#include "HCSR04.h"

IRrecv Empfaenger(IR_PIN);
decode_results Daten;
UltraSonicDistanceSensor Abstandssensor(TRIGPIN, ECHOPIN);

float Abstand = 0.0;
int letzterInfrarotbefehl = 0;
int Eingabebefehl = 0;
byte aktuelleBetriebsart = 5;
byte aktuelleLeistungR = 0;
byte ZielleistungR = 0;
byte aktuelleLeistungL = 0;
byte ZielleistungL = 0;
long AusweichTimer = 0;

void setup() {
  pinMode(MR_A, OUTPUT); pinMode(MR_B, OUTPUT); pinMode(MR_PWM, OUTPUT);
  pinMode(ML_A, OUTPUT); pinMode(ML_B, OUTPUT); pinMode(ML_PWM, OUTPUT);
  Empfaenger.enableIRIn(); 
  Serial.begin(9600);
}

void loop() {

  // Wenn 
  
  if (Empfaenger.decode(&Daten))
  {
     if(Daten.value != letzterInfrarotbefehl)
     {
       Eingabebefehl = Daten.value % 0x800;
       letzterInfrarotbefehl = Daten.value;
     }      
     Empfaenger.resume();
  }


  switch(Eingabebefehl)    // Eingabe verarbeiten
  {
    case 1: 
      aktuelleLeistungR = aktuelleLeistungL = 255;
      ZielleistungR = STUFE2;
      ZielleistungL = STUFE1;
      aktuelleBetriebsart = 1;
    break;
        
    case 2:
      if(aktuelleBetriebsart == 2)
        ZielleistungR = ZielleistungL = STUFE2;
      else
      {
        aktuelleLeistungR = aktuelleLeistungL = 255;
        ZielleistungR = ZielleistungL = STUFE1;
      }
      aktuelleBetriebsart = 2;
    break;

    case 3:
      aktuelleLeistungR = aktuelleLeistungL = 255;
      ZielleistungR = STUFE1;
      ZielleistungL = STUFE2;
      aktuelleBetriebsart = 3;
    break;

    case 4: 
      aktuelleLeistungR = aktuelleLeistungL = 255;
      ZielleistungR = ZielleistungL = STUFE1;      
      aktuelleBetriebsart = 4;
    break;

    case 5:
      aktuelleBetriebsart = 5;
    break;

    case 6: 
      aktuelleLeistungR = aktuelleLeistungL = 255;
      ZielleistungR = ZielleistungL = STUFE1;
      aktuelleBetriebsart = 6;
    break;

    case 7: 
      aktuelleLeistungR = aktuelleLeistungL = 255;
      ZielleistungR = STUFE2;
      ZielleistungL = STUFE1;
      aktuelleBetriebsart = 7;
    break;

    case 8:
      if(aktuelleBetriebsart == 8)
        ZielleistungR = ZielleistungL = STUFE2;
      else
      {
        ZielleistungR = ZielleistungL = STUFE1;
        aktuelleLeistungR = aktuelleLeistungL = 255;
      }
      aktuelleBetriebsart = 8;
    break;

    case 9: 
      aktuelleLeistungR = aktuelleLeistungL = 255;
      ZielleistungR = STUFE1;
      ZielleistungL = STUFE2;
      aktuelleBetriebsart = 9;
    break;
  }

  Eingabebefehl = 0;


  // abhängig von der aktuellen Betriebsart
  // werden nun die Motoren angesteuert:
  
  switch(aktuelleBetriebsart)   // Fahren
  {
    case 1: case 2: case 3:
      Richtung(MR, VOR);
      Richtung(ML, VOR);
      analogWrite(MR_PWM, aktuelleLeistungR);
      analogWrite(ML_PWM, aktuelleLeistungL);
      Abstand = Abstandssensor.measureDistanceCm();
      if(Abstand < 5.0)
      {
        if(random(2))
        {
          aktuelleBetriebsart = 7;
          ZielleistungR = STUFE2;
          ZielleistungL = STUFE1;
        }
        else
        {
          aktuelleBetriebsart = 9;
          ZielleistungR = STUFE1;
          ZielleistungL = STUFE2;         
        }

        aktuelleLeistungR = aktuelleLeistungL = 255;
        AusweichTimer = millis() + 2000;
      }
    break;
    case 4:
      Richtung(MR, VOR);
      Richtung(ML, RUECK);
      analogWrite(MR_PWM, aktuelleLeistungR);
      analogWrite(ML_PWM, aktuelleLeistungL);
    break;
    case 5:
      ZielleistungR = ZielleistungL = 0;
      analogWrite(MR_PWM, aktuelleLeistungR);
      analogWrite(ML_PWM, aktuelleLeistungL);
    break;
    case 6:
      Richtung(MR, RUECK);
      Richtung(ML, VOR);
      analogWrite(MR_PWM, aktuelleLeistungR);
      analogWrite(ML_PWM, aktuelleLeistungL);
    break;  
    case 7: case 8: case 9:
      Richtung(MR, RUECK);
      Richtung(ML, RUECK);
      analogWrite(MR_PWM, aktuelleLeistungR);
      analogWrite(ML_PWM, aktuelleLeistungL);
    break;
  }


  if(aktuelleLeistungL < ZielleistungL)
    aktuelleLeistungL++;
  if(aktuelleLeistungL > ZielleistungL)
    aktuelleLeistungL--;

  if(aktuelleLeistungR < ZielleistungR)
    aktuelleLeistungR++;
  if(aktuelleLeistungR > ZielleistungR)
    aktuelleLeistungR--;

  if(millis() > AusweichTimer && AusweichTimer != 0)
  {
    aktuelleBetriebsart = 2;
    ZielleistungR = ZielleistungL = STUFE1;
    aktuelleLeistungR =  aktuelleLeistungL = 255;
    AusweichTimer = 0;
  }
  
  delay(1);
}


void Richtung(byte Motor, byte Richtung)
{
  byte Pin_a = (Motor == ML) ? ML_A : MR_A;
  byte Pin_b = (Motor == ML) ? ML_B : MR_B;

  if(Richtung == VOR)
  {
    digitalWrite(Pin_a, HIGH); 
    digitalWrite(Pin_b, LOW); 
  }
  else
  {
    digitalWrite(Pin_a, LOW); 
    digitalWrite(Pin_b, HIGH); 
  }
}
