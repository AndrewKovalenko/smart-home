#include <ESP8266WiFi.h>
#include "wifiAccessPoint.h"

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  startWiFiAccessPoint();
}

void loop()
{
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
