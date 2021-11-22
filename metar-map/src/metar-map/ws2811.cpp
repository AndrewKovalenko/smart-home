#include "ws2811.h"
#define NUMBER_OF_LEDS 50

CRGBArray<NUMBER_OF_LEDS> leds;

WS2811LedStrip::WS2811LedStrip(uint8_t numberOfLeds)
{
    FastLED.addLeds<WS2811,5>(this.leds, NUMBER_OF_LEDS); 
}

WS2811LedStrip::~WS2811LedStrip()
{
}

void WS2811LedStrip:setLedColor(int ledNumber, LedColor color)
{ 
    leds[ledNumber] = CRGB(color.red, color.blue, color.green);
    FastLED.show();
}

