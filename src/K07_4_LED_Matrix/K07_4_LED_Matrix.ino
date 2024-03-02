#include "LedControl.h"

#define DATA_IN 12
#define CS 11
#define CLK 10

LedControl Anzeige = LedControl(DATA_IN, CLK, CS, 1);

void setup() {
  Anzeige.shutdown(0,false);
  Anzeige.setIntensity(0,8);
  Anzeige.clearDisplay(0);
}

void loop() { 
  Anzeige.setRow(0,0,B00000000); // A
  Anzeige.setRow(0,1,B00111100);
  Anzeige.setRow(0,2,B01000010);
  Anzeige.setRow(0,3,B01111110);
  Anzeige.setRow(0,4,B01000010);
  Anzeige.setRow(0,5,B01000010);
  Anzeige.setRow(0,6,B01000010);
  Anzeige.setRow(0,7,B00000000);
  delay(500);
  Anzeige.setRow(0,1,B00000000); // r
  Anzeige.setRow(0,2,B00000000);
  Anzeige.setRow(0,3,B00111110);
  Anzeige.setRow(0,4,B01000000);
  Anzeige.setRow(0,5,B01000000);
  Anzeige.setRow(0,6,B01000000);
  delay(500);
  Anzeige.setRow(0,1,B00000010); // d
  Anzeige.setRow(0,2,B00000010);
  Anzeige.setRow(0,3,B00111110);
  Anzeige.setRow(0,4,B01000010);
  Anzeige.setRow(0,5,B01000010);
  Anzeige.setRow(0,6,B00111100);
  delay(500);
  Anzeige.setRow(0,1,B00000000); // u
  Anzeige.setRow(0,2,B00000000);
  Anzeige.setRow(0,3,B01000010);
  Anzeige.setRow(0,4,B01000010);
  Anzeige.setRow(0,5,B01000010);
  Anzeige.setRow(0,6,B01111100);
  delay(500);
  Anzeige.setRow(0,1,B00001000); // i
  Anzeige.setRow(0,2,B00000000);
  Anzeige.setRow(0,3,B00001000);
  Anzeige.setRow(0,4,B00001000);
  Anzeige.setRow(0,5,B00001000);
  Anzeige.setRow(0,6,B00011100);
  delay(500);
  Anzeige.setRow(0,1,B00000000); // n
  Anzeige.setRow(0,2,B00000000);
  Anzeige.setRow(0,3,B01111100);
  Anzeige.setRow(0,4,B01000010);
  Anzeige.setRow(0,5,B01000010);
  Anzeige.setRow(0,6,B01000010);
  delay(500);
  Anzeige.setRow(0,1,B00000000); // 0
  Anzeige.setRow(0,2,B00000000);
  Anzeige.setRow(0,3,B00111100);
  Anzeige.setRow(0,4,B01000010);
  Anzeige.setRow(0,5,B01000010);
  Anzeige.setRow(0,6,B00111100);
  delay(500);
  Anzeige.clearDisplay(0);
  delay(500);
}
