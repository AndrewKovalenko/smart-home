#include <Arduino.h>
#include "src/ledController/ws2811.h"
#include "src/weatherColorCodes.h"

WS2811LedStrip ledStrip;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  for (uint8_t i = 1; i <= 50; i++)
  {
    ledStrip.setLedColor(i, LIFR);
  }

  for (uint8_t i = 1; i <= 50; i++)
  {
    ledStrip.setLedColor(i, IFR);
  }

  for (uint8_t i = 1; i <= 50; i++)
  {
    ledStrip.setLedColor(i, MVFR);
  }

  for (uint8_t i = 1; i <= 50; i++)
  {
    ledStrip.setLedColor(i, VFR);
  }
}
