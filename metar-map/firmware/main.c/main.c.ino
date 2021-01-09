#include <ESP8266WiFi.h>

#include "wifiAccessPoint.h"
#include "httpServer.h"

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  startWiFiAccessPoint();
  Serial.println(WiFi.softAPIP());

  startAccessPointConfigWebServer();
}

void loop()
{
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
