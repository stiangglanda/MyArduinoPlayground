#include "Wire.h"       
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD(39, 16, 2);

void setup()
{
  LCD.init();
  LCD.clear();
  LCD.backlight();
  LCD.setCursor(2, 0);
  LCD.print("Hallo, Welt!");
  LCD.setCursor(1, 1);
  LCD.print("Hallo, Arduino!");
  delay(5000);
  LCD.clear();
}

void loop()
{
  LCD.setCursor(2, 0);
  LCD.print(millis()/1000);
  delay(1000);
}
