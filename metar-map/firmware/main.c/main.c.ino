//#define FASTLED_ESP8266_D1_PIN_ORDER
#include "FastLED.h"

#define NUM_LEDS 50
#define OUTPUT_PIN 5 //D1

CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<WS2811, OUTPUT_PIN, RGB>(leds, NUM_LEDS); 
  FastLED.setBrightness(84);
}

void loop() {
  for(int x = 0; x < NUM_LEDS; x++){
             leds[x] = CRGB::Green;
  }
  FastLED.show();
  delay(300);


  for(int x = 0; x < NUM_LEDS; x++){
             leds[x] = CRGB::Black;
  }
  FastLED.show();
  delay(300);
}
