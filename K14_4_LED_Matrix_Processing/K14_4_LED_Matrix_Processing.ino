#include "FastLED.h"

#define NUM_LEDS 64
#define DATA_PIN 3
#define PAKETLAENGE 15

CRGB leds[NUM_LEDS];

char Datenpaket[PAKETLAENGE];

void setup() {
 Serial.begin(57600);
 FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); 
}

void loop() {
  
  if(empfangen())
  {
    auswerten();
  }
}


boolean empfangen() {
 static byte Zaehler = 0;
 char Endmarkierung = '\n';
 char Empfangsbyte;
 

 while (Serial.available() > 0)
 {
   Empfangsbyte = Serial.read();
  
   if(Empfangsbyte != Endmarkierung) 
   {
     Datenpaket[Zaehler] = Empfangsbyte;
     Zaehler++;
     if (Zaehler >= PAKETLAENGE)
       Zaehler = PAKETLAENGE - 1;
   }
   else 
   {
     Datenpaket[Zaehler] = '\0'; 
     Zaehler = 0;
     return true;
   }
 }
 return false;
}

void auswerten()
{
  byte LEDnr, r, g, b = 0;  

  if(Datenpaket[0] == 'A' && (Datenpaket[12] == 'E' || Datenpaket[12] == 'N' ))
  {
    LEDnr = (Datenpaket[1]-'0') * 10 + (Datenpaket[2]-'0');
    r = (Datenpaket[3]-'0') * 100 + (Datenpaket[4]-'0') * 10 + (Datenpaket[5]-'0');
    g = (Datenpaket[6]-'0') * 100 + (Datenpaket[7]-'0') * 10 + (Datenpaket[8]-'0');
    b = (Datenpaket[9]-'0') * 100 + (Datenpaket[10]-'0') * 10 + (Datenpaket[11]-'0');

    leds[LEDnr] = CRGB(r, g, b); 
    if(Datenpaket[12] == 'E')  
      FastLED.show();
  }
}
