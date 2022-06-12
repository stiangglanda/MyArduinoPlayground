#include "DS3231.h" 
#include "Wire.h"

DS3231 Uhr;

boolean Dummy;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  Uhr.setDate(1);
  Uhr.setMonth(5);
  Uhr.setYear(19);
  Uhr.setHour(11);
  Uhr.setMinute(9);
  Uhr.setSecond(0);
}

void loop()
{
  Serial.print("Datum: ");
  Serial.print(Uhr.getDate());
  Serial.print(".");
  Serial.print(Uhr.getMonth(Dummy));
  Serial.print(".");
  Serial.print(Uhr.getYear());

  Serial.print("  Uhrzeit: ");
  Serial.print(Uhr.getHour(Dummy,Dummy));
  Serial.print(":");
  if(Uhr.getMinute() < 10)
    Serial.print("0");
  Serial.print(Uhr.getMinute());
  Serial.print(":");
  if(Uhr.getSecond() < 10)
    Serial.print("0");
  Serial.println(Uhr.getSecond());

  delay(1000);
}
