#include "Keypad.h"

#define ZEILENZAHL 4
#define SPALTENZAHL 4

char Tasten[ZEILENZAHL][SPALTENZAHL] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte ZeilenPins[ZEILENZAHL] = {2,3,4,5}; 
byte SpaltenPins[ZEILENZAHL] = {6,7,8,9}; 

Keypad Tastatur = Keypad( makeKeymap(Tasten), ZeilenPins, SpaltenPins, ZEILENZAHL, SPALTENZAHL); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char Eingabe = Tastatur.getKey();
  
  if(Eingabe){
    Serial.print("Taste wurde gedrückt: ");
    Serial.println(Eingabe);
  }
}
