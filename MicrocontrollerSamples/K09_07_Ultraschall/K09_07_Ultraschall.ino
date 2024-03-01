#define ECHOPIN 13
#define TRIGPIN 12

#include "HCSR04.h"

UltraSonicDistanceSensor Abstandssensor(TRIGPIN, ECHOPIN);  

void setup () {
    Serial.begin(9600);  
}

void loop () {
    Serial.print("Abstand: ");
    Serial.print(Abstandssensor.measureDistanceCm());
    Serial.println(" cm");
    delay(500);
}
