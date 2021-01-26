#include "time.h"
#include "deviceMode.h"
#include "settingsStorage.h"
#include "wifiAccessPoint.h"
#include "httpServer.h"
#include "wifiStation.h"

const unsigned char RECONNECT_ATTEMPTS = 3;

void startCongigurationAccessPoint()
{
  Serial.println("Setting AP (Access Point)…");

  IPAddress localIpAddress = startWiFiAccessPoint();

  Serial.println("WiFi local IP address: ");
  Serial.println(localIpAddress);

  Serial.println("Starting HTTP Server");
  startAccessPointConfigWebServer();
}

DeviceMode currentMode;

void setup()
{
  Serial.begin(115200);

  WiFiCredentials savedCredentials = readWifiCredentials();

  Serial.println("Saved SSID: " + savedCredentials.ssid);

  if (blancCredentialsRecord(savedCredentials))
  {
    uint16_t calculatedCRC = calculateCRC(savedCredentials.ssid + savedCredentials.password);
    Serial.printf("crc didn't match: %d vs %d", calculatedCRC, savedCredentials.crc);
    startCongigurationAccessPoint();
    currentMode = DeviceMode::AccessPoint;
  }
  else
  {
    Serial.println("crc matched, starting WiFI client!");
    Serial.println("SSID: " + savedCredentials.ssid + ", Password: " + savedCredentials.password);

    unsigned char connectionResult = startWiFiClient(savedCredentials, RECONNECT_ATTEMPTS);

    if (connectionResult == WIFI_CONNECTION_SUCCESSFULL)
    {
      currentMode = DeviceMode::WiFiClient;
    }
    else
    {
      resetCredentialsStorage();
      ESP.restart();
    }
  }
}

void loop()
{
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
  httpServer.handleClient();
}
