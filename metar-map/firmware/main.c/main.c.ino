#include "wifiAccessPoint.h"
#include "httpServer.h"

void setup()
{
  Serial.begin(115200);

  Serial.println("Setting AP (Access Point)…");

  IPAddress localIpAddress = startWiFiAccessPoint();

  Serial.println("WiFi local IP address: ");
  Serial.println(localIpAddress);

  Serial.println("Starting HTTP Server");
  startAccessPointConfigWebServer();
}

void loop()
{
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
  httpServer.handleClient();
}
