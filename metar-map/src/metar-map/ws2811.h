struct LedColor
{
    uint8_t red;
    uint8_t blue;
    uint8_t green;
};

void initializeLedStrip();
void setLed(int ledNumber, LedColor color);
