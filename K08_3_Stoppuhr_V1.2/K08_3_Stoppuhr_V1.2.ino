#define TASTE 3
#define MILLISPROSTUNDE 3600000
#define MILLISPROMINUTE 60000

#include "Wire.h"
#include "Adafruit_SSD1306.h"

Adafruit_SSD1306 display(128, 64);  // Argumente: Displaybreite und -höhe

long Timer = 0;

long Startzeit = 0;
long Stoppzeit = 0;
long Zeitdifferenz = 0;

byte Stunden; byte Minuten; byte Sekunden; int Tausendstel;   // In dieser Zeile war im Buch ein Tippfehler (byte statt int).

boolean aktiv = false;

void setup()   {   
  pinMode(TASTE, INPUT_PULLUP);
          
  display.begin(SSD1306_SWITCHCAPVCC, 60);

  display.clearDisplay();
  display.setTextColor(WHITE);

}

void loop() {
  if(millis() > Timer)
  {
    if(aktiv)
      Zeitdifferenz = millis()-Startzeit;
    else
      Zeitdifferenz = Stoppzeit-Startzeit;
      
    Stunden = Zeitdifferenz / MILLISPROSTUNDE;
    Minuten = (Zeitdifferenz % MILLISPROSTUNDE) / MILLISPROMINUTE;
    Sekunden = (Zeitdifferenz % MILLISPROMINUTE) / 1000;
    Tausendstel = Zeitdifferenz % 1000;

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(17,2);
    display.println("Stoppuhr");
    display.drawLine(17,20,  110,20, WHITE);
    
    display.setTextSize(1);
    display.setCursor(40,30);
    if(aktiv)
      display.println("aktiv!");
    else
      display.println("Resultat:");
      
    display.setCursor(30,50);
    if(Stunden < 10)
      display.print("0");
    display.print(Stunden);
    display.print(":");
    if(Minuten < 10)
      display.print("0");
    display.print(Minuten);
    display.print(":");
    if(Sekunden < 10)
      display.print("0");
    display.print(Sekunden);
    if(!aktiv)
    {
      display.print(".");
      if(Tausendstel < 100)
        display.print("0");
      if(Tausendstel < 10)
        display.print("0");
      display.print(Tausendstel);
    }
    display.display();
  
    Timer = millis() + 1000;
  }

  if(!digitalRead(TASTE))
  {
    if(aktiv)
    {
      Stoppzeit = millis();
      aktiv = false;
      Timer = 0;
    }
    else
    {
      Startzeit = millis();
      aktiv = true;
      Timer = 0;
    }
    while(!digitalRead(TASTE));
  }
}
