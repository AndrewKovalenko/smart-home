#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <FastLED.h>

#define NUMBER_OF_LEDS 50

struct LedColor
{
    uint8_t red;
    uint8_t blue;
    uint8_t green;
};

class WS2811LedStrip
{
private:
    CRGBArray<NUMBER_OF_LEDS> leds;

public:
    WS2811LedStrip();
    void setLedColor(int ledNumber, LedColor color);
    void apply();
};

#endif