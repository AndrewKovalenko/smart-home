#include <ESP8266WiFi.h>
#include "../utils/stringUtils.h"
#include "../weather/weatherColorCodes.h"
#include "../httpClient/http-client.h"
#include "../weather/weatherDataRetriever.h"
#include "../settingsStorage/storage.h"
#include "../settingsStorage/storage.h"
#include "../weather/weatherStation.h"
#include "../wifiAccessPoint/accessPoint.h"
#include "../wifiAccessPoint/configurationHttpServer.h"
#include "boardManager.h"
#include "stationsToLedsMapping.h"

#define WIFI_RECONNECT_DELAY 1000
#define MAX_CONNECTION_ATTEMPTS 15

BoardManager::BoardManager(String baseUrl)
{
    weatherReadingUrl = buildWeatherRetrievingUrl(baseUrl, metarStations);
    httpServer = NULL;
    ledStrip = WS2811LedStrip();
    _boardMode = readMode();
}

BoardMode BoardManager::readMode()
{
    WiFiCredentials* credentialsSaved = readWifiCredentials();
    
    Serial.println("SSID: " + String(credentialsSaved->ssid));
    Serial.println("Password: " + String(credentialsSaved->password));
    Serial.println("Crc: " + String(credentialsSaved->crc));

    BoardMode boardMode = areCredentialsBlank(*credentialsSaved) ? WiFiSetup : WeatherClient;
    delete credentialsSaved;
    return boardMode;
}

BoardMode BoardManager::boardMode()
{
    return _boardMode;
}

void BoardManager::startInWiFiSetupMode()
{
    startWiFiAccessPoint();
    httpServer = startAccessPointConfigWebServer();
}

void BoardManager::handleHttpClient()
{
    if(httpServer != NULL)
    {
      httpServer->handleClient();
    }
}

void BoardManager::connectToWiFiNetwork()
{
    Serial.println("Connecting to network");
    uint8_t connectionAttempts = 0;
    WiFiCredentials *savedCredentials = readWifiCredentials();

    WiFi.begin(savedCredentials->ssid, savedCredentials->password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(WIFI_RECONNECT_DELAY);
        Serial.print(".");
        connectionAttempts++;

        if (connectionAttempts > MAX_CONNECTION_ATTEMPTS)
        {
            Serial.println("Unable to connect to WiFi network " + String(savedCredentials->ssid) +
                           " with password" + String(savedCredentials->password));
            resetCredentialsStorage();

            delete savedCredentials;

            Serial.println("Restarting...");
            ESP.restart();
        }
    }
}

void BoardManager::startHttpServer()
{
}

void BoardManager::displayWeatherOnTheMap()
{
  Serial.println(weatherReadingUrl);
  String result = makeGetCall(weatherReadingUrl);
  const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));
  Serial.println("Number of stations");
  Serial.println(numberOfStations);
  parseResponse(result, metarStations, numberOfStations);

  for (uint8_t i = 0; i < numberOfStations; i++)
  {
    LedColor colorForCurrentStation;

    switch (metarStations[i].weather[0])
    {
    case 'V':
      colorForCurrentStation = VFR_COLOR;
      break;

    case 'M':
      colorForCurrentStation = MVFR_COLOR;
      break;

    case 'I':
      colorForCurrentStation = IFR_COLOR;
      break;

    case 'L':
      colorForCurrentStation = LIFR_COLOR;
      break;

    default:
      colorForCurrentStation = NO_DATA_COLOR;
    }

    Serial.println("|" + metarStations[i].stationName + "|" + metarStations[i].weather + "|");
    ledStrip.setLedColor(metarStations[i].ledNumber, colorForCurrentStation);
    ledStrip.apply();
  }
}