#include <Arduino.h>
//  #include <ESP8266WiFi.h>
//  #include <ESP8266WiFiMulti.h>

// #include "http-client.h"
#include "ws2811.h"

//  ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  initializeLedStrip();
  // Serial.println();
  // Serial.println();
  // Serial.println();

  // for (uint8_t t = 4; t > 0; t--) {
  //   Serial.printf("[SETUP] WAIT %d...\n", t);
  //   Serial.flush();
  //   delay(1000);
  // }

  // WiFi.mode(WIFI_STA);
  // WiFiMulti.addAP("BrainBurner", "Sw6%H0mE!");
}

void loop() {
   for (uint8_t color = 0; color < 255; color++)
   {
     for (int i = 1; i <= 50; i++)
     {
       LedColor rgbColor = {color, color, color};
       setLed(i, rgbColor);
       delay(10000);
     }    
   }
  
  // // wait for WiFi connection
  // if ((WiFiMulti.run() == WL_CONNECTED)) {
  //   String payload = makeGetCall("https://www.aviationweather.gov/adds/dataserver_current/httpparam?datasource=metars&requestType=retrieve&format=csv&mostRecentForEachStation=constraint&hoursBeforeNow=1.25&stationString=KPAE%20KSEA");

  //   Serial.println(payload);
  // }

  // Serial.println("Wait 10s before next round...");
  // delay(10000);
}
