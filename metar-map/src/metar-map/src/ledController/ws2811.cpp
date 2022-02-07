#include "ws2811.h"

#define DATA_PIN 5

WS2811LedStrip::WS2811LedStrip()
{
    FastLED.addLeds<WS2811, DATA_PIN>(leds, NUMBER_OF_LEDS); 
}

void WS2811LedStrip::setLedColor(int ledNumber, LedColor color)
{ 
    leds[ledNumber] = CRGB(color.red, color.blue, color.green);
}

void WS2811LedStrip::apply()
{
    FastLED.show();
}