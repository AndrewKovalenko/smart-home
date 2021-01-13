#include "wifiAccessPoint.h"
#include "httpServer.h"
#include "settingsStorage.h"

void startCongigurationAccessPoint()
{
  Serial.println("Setting AP (Access Point)…");

  IPAddress localIpAddress = startWiFiAccessPoint();

  Serial.println("WiFi local IP address: ");
  Serial.println(localIpAddress);

  Serial.println("Starting HTTP Server");
  startAccessPointConfigWebServer();
}

void setup()
{
  Serial.begin(115200);

  WiFiCredentials savedCredentials = readCredentials();

  if (savedCredentials.ssid == "" || savedCredentials.password == "")
  {
    startCongigurationAccessPoint();
  }
  else
  {
    Serial.println("SSID: " + savedCredentials.ssid + ", Password: " + savedCredentials.password);
  }
}

void loop()
{
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
  httpServer.handleClient();
}
