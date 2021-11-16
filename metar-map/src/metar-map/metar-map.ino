#include <Arduino.h>
#include <FastLED.h>
#define NUMBER_OF_LEDS 50

struct LedColor
{
    uint8_t red;
    uint8_t blue;
    uint8_t green;
};

CRGBArray<NUMBER_OF_LEDS> leds;

void initializeLedStrip() 
{ 
    FastLED.addLeds<WS2811,5>(leds, NUMBER_OF_LEDS); 
}

void setLed(int ledNumber, LedColor color){ 
    leds[ledNumber] = CRGB(color.red, color.blue, color.green);
}

void setup() {

  Serial.begin(115200);
  initializeLedStrip();
}

void loop() {
   for (uint8_t color = 0; color < 255; color++)
   {
     for (int i = 1; i <= 50; i++)
     {
       LedColor rgbColor = {color, color, color};
       setLed(i, rgbColor);
       FastLED.delay(33);
     }    

     leds.fadeToBlackBy(NUMBER_OF_LEDS);
   }
}
