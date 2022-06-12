#define TASTE_A 6
#define TASTE_B 7

#include "LiquidCrystal_I2C.h"
#include "DS3231.h" 
#include "DHT.h"

LiquidCrystal_I2C LCD(39,16,2); 

DS3231 Uhr;

DHT dhtSensor(2, DHT22);

boolean Dummy = false;
long Timer = 0;
float Temp; float maxTemp = -100.0; float minTemp = 100.0;
float Feuchte;  float maxFeuchte = 0.0; float minFeuchte = 100.0;
boolean zeigeMinMax = false;

byte maxPfeil[8] = {B00100,
                    B01110,
                    B11111,
                    B01110,
                    B01110,
                    B01110,
                    B01110,
                    B00000};
byte minPfeil[8] = {B00000,
                    B01110,
                    B01110,
                    B01110,
                    B01110,
                    B11111,
                    B01110,
                    B00100};

void setup()
{
  pinMode(TASTE_A, INPUT_PULLUP);
  pinMode(TASTE_B, INPUT_PULLUP);

  LCD.init();        
  LCD.createChar(0, maxPfeil);    
  LCD.createChar(1, minPfeil);   
  LCD.clear();
  LCD.backlight();
  LCD.setCursor(2,0);

  dhtSensor.begin();
}

void loop()
{
  if(millis() > Timer)
  {
    Temp = dhtSensor.readTemperature();
    Feuchte = dhtSensor.readHumidity();

    if(Temp > maxTemp)
      maxTemp = Temp;
    if(Temp < minTemp)
      minTemp = Temp;
    if(Feuchte > maxFeuchte)
      maxFeuchte = Feuchte;
    if(Feuchte < minFeuchte)
      minFeuchte = Feuchte;

    if(zeigeMinMax)
    {
      LCD.setCursor(0,0);
      LCD.print("T: ");
      LCD.print((char)0);
      LCD.print(maxTemp,1);
      LCD.setCursor(10,0);
      LCD.print((char)1);
      LCD.print(minTemp,1);

      LCD.setCursor(0,1);
      LCD.print("F: ");
      LCD.print((char)0);
      LCD.print(maxFeuchte,1);
      LCD.setCursor(10,1);
      LCD.print((char)1);
      LCD.print(minFeuchte,1);      
    }
    else
    {
      LCD.setCursor(0,0);
      
      if(Uhr.getDate() < 10)
        LCD.print("0");
      LCD.print(Uhr.getDate());
      
      LCD.print(".");
      
      if(Uhr.getMonth(Dummy) < 10)
        LCD.print("0");
      LCD.print(Uhr.getMonth(Dummy));
      
      LCD.print(".");
      
      if(Uhr.getYear() < 10)
        LCD.print("0");
      LCD.print(Uhr.getYear());
  
      LCD.print("  T:");
      LCD.print(Temp,1);
    
      LCD.setCursor(0,1);
      
      if(Uhr.getHour(Dummy, Dummy) < 10)
        LCD.print("0");
      LCD.print(Uhr.getHour(Dummy, Dummy));
      
      LCD.print(":");
      
      if(Uhr.getMinute() < 10)
        LCD.print("0");
      LCD.print(Uhr.getMinute());
      
      LCD.print(":");
      
      if(Uhr.getSecond() < 10)
        LCD.print("0");
      LCD.print(Uhr.getSecond());
  
      LCD.print("  F:");
      LCD.print(Feuchte,1);     
    }
    Timer = millis() + 1000;
  }

  if(!digitalRead(TASTE_B))
  {
    while(!digitalRead(TASTE_B));
      
    if(zeigeMinMax)
    {
      maxTemp = -100.0; minTemp = 100.0;
      maxFeuchte = 0.0; minFeuchte = 100.0;
      LCD.clear();
      Timer = 0;
    }
    else
    {
      Uhr.setDate(Einstellen(Uhr.getDate(), 1, 31, 0, 0));
      Uhr.setMonth(Einstellen(Uhr.getMonth(Dummy), 1, 12, 3, 0));
      Uhr.setYear(Einstellen(Uhr.getYear(), 19, 29, 6, 0));
      Uhr.setHour(Einstellen(Uhr.getHour(Dummy, Dummy), 0, 23, 0, 1));
      Uhr.setMinute(Einstellen(Uhr.getMinute(), 0, 59, 3, 1));
      Uhr.setSecond(0);
    }
  }

  if(!digitalRead(TASTE_A))
  {
    while(!digitalRead(TASTE_A));
    
    zeigeMinMax = !zeigeMinMax;
    LCD.clear();
    Timer = 0;
  }
}


byte Einstellen(byte aktuellerWert, byte minimalWert, byte maximalWert, byte posX, byte posY)
{
  while(digitalRead(TASTE_B))
  {
    LCD.setCursor(posX, posY);
    if(millis()%1000 > 800)
    {
      LCD.print("__");
    }
    else
    {
      if(aktuellerWert < 10)
        LCD.print("0");
      LCD.print(aktuellerWert);
    }

    if(!digitalRead(TASTE_A))
    {
      aktuellerWert++;
      if(aktuellerWert > maximalWert)
        aktuellerWert = minimalWert;
      while(!digitalRead(TASTE_A));
    }
  }

  while(!digitalRead(TASTE_B));
    
  LCD.setCursor(posX, posY);
  if(aktuellerWert < 10)
    LCD.print("0");
  LCD.print(aktuellerWert);

  return aktuellerWert;
}
