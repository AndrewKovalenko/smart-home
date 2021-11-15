#include <FastLED.h>

#define NUMBER_OF_LEDS 50

typedef struct RGB
{
    uint8_t red;
    uint8_t blue;
    uint8_t green;
};

CRGBArray<NUMBER_OF_LEDS> leds;

void initializeLedStrip() 
{ 
    FastLED.addLeds<WS2811,5>(leds, NUM_LEDS); 
}

void setLed(int ledNumber, RGB color){ 
    leds[ledNumber] = CHSV(color.red, color.blue, color.green);
}
