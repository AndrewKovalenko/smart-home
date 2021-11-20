#include <FastLED.h>
#include "ws2811.h"
#define NUMBER_OF_LEDS 50

CRGBArray<NUMBER_OF_LEDS> leds;

void initializeLedStrip() 
{ 
    FastLED.addLeds<WS2811,5>(leds, NUMBER_OF_LEDS); 
}

void setLed(int ledNumber, LedColor color)
{ 
    leds[ledNumber] = CRGB(color.red, color.blue, color.green);
}

void applyLedSettings()
{
    FastLED.show();
}

class WS2811LedStrip
{
private:
    CRGBArray<NUMBER_OF_LEDS> leds;

public:
    WS2811LedStrip(uint8_t numberOfLeds);
    ~WS2811LedStrip();
};

WS2811LedStrip::WS2811LedStrip(uint8_t numberOfLeds)
{
    FastLED.addLeds<WS2811,5>(this.leds, NUMBER_OF_LEDS); 
}

WS2811LedStrip::~WS2811LedStrip()
{
}

