#include <Arduino.h>
#include "ws2811.h"

void setup() {

  Serial.begin(115200);
  initializeLedStrip();
}

void loop() {
   for (uint8_t color = 0; color < 255; color++)
   {
     for (int i = 1; i <= 50; i++)
     {
       LedColor rgbColor = {color, color, color};
       setLed(i, rgbColor);
       applyLedSettings();
     }    
   }
}
