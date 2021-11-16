#include <FastLED.h>
#include "ws2811.h"
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

