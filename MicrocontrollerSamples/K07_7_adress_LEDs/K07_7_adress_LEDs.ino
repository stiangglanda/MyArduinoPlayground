#include "FastLED.h"

#define NUM_LEDS 64
#define DATA_PIN 3

CRGB leds[NUM_LEDS];
byte Farbe;
byte Position = 0;

void setup() { 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); 
}

void loop() { 
  leds[Position++] = CHSV(Farbe++, 255, 200);     
  FastLED.show();
  delay(50);
  fadeToBlackBy(leds, NUM_LEDS, 20);
  if(Position > NUM_LEDS-1)
    Position = 0;
}
