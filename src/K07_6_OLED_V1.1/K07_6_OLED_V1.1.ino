#include "Wire.h"
#include "Adafruit_SSD1306.h"

Adafruit_SSD1306 display(128, 64);    // Argumente: Displaybreite und -höhe

void setup()   {           
  display.begin(SSD1306_SWITCHCAPVCC, 60);
}

void loop() {
  display.clearDisplay();

  display.fillRect(0, 0, 127, 63, WHITE);
  display.fillRect(10, 10, 107, 43, BLACK);
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,25);
  display.print("Hallo!");
  display.display();
  delay(5000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("Das ist ein");
  display.println("zweizeiliger Text."); 
  display.display();
  
  for(byte i = 0; i < 128; i++)
  {
    display.drawLine(0,40,  i,40, WHITE);
    display.display();
    delay(30);   
  }
}
