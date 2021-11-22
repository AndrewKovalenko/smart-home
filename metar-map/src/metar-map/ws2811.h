#include <FastLED.h>

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
    WS2811LedStrip(uint8_t numberOfLeds);
    ~WS2811LedStrip();

    void setColor();
};

void initializeLedStrip();
void setLedColor(int ledNumber, LedColor color);
void applyLedSettings();
