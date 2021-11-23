#include "ws2811.h"

WS2811LedStrip::WS2811LedStrip()
{
    FastLED.addLeds<WS2811,5>(leds, NUMBER_OF_LEDS); 
}

void WS2811LedStrip::setLedColor(int ledNumber, LedColor color)
{ 
    leds[ledNumber] = CRGB(color.red, color.blue, color.green);
    FastLED.show();
}