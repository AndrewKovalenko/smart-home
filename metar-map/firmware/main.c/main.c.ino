#include "settingsStorage.h"
#include "wifiAccessPoint.h"
#include "httpServer.h"

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

  WiFiCredentials savedCredentials = readWifiCredentials();

  if (blancCredentialsRecord(savedCredentials))
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
