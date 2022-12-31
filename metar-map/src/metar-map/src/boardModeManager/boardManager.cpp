#include <ESP8266WiFi.h>
#include <FastLED.h>

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
  weatherReadingUrl = buildWeatherRetrievingUrl(baseUrl, metarStations, NUMBER_OF_STATIONS);
  httpServer = NULL;
  // ledStrip = WS2811LedStrip();
  _boardMode = readMode();
}

BoardMode BoardManager::readMode()
{
  WiFiCredentials *credentialsSaved = readWifiCredentials();

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
  if (httpServer != NULL)
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
      resetCredentialsStorage();
      delete savedCredentials;
      ESP.restart();
    }
  }
}

void BoardManager::displayWeatherOnTheMap()
{
  String result = makeGetCall(weatherReadingUrl);
  const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));
  parseResponse(result, metarStations, numberOfStations);

  CRGBArray<50> leds;
  FastLED.addLeds<WS2811, 5>(leds, 50);
  FastLED.setBrightness(60);

  for (uint8_t i = 0; i < 50; i++)
  {
    bool ledWeatherSet = false;
    for (uint8_t j = 0; j < numberOfStations; j++)
    {
      if (i == metarStations[j].ledNumber)
      {
        // LedColor colorForCurrentStation;

        // switch (metarStations[j].weather[0])
        // {
        // case 'V':
        //   colorForCurrentStation = VFR_COLOR;
        //   break;

        // case 'M':
        //   colorForCurrentStation = MVFR_COLOR;
        //   break;

        // case 'I':
        //   colorForCurrentStation = IFR_COLOR;
        //   break;

        // case 'L':
        //   colorForCurrentStation = LIFR_COLOR;
        //   break;

        // default:
        //   colorForCurrentStation = NO_DATA_COLOR;
        // }

        CRGB colorForCurrentStation;
        switch (metarStations[j].weather[0])
        {
        case 'V':
          colorForCurrentStation = CRGB(34, 197, 1);
          break;

        case 'M':
          colorForCurrentStation = CRGB(31, 112, 219);
          break;

        case 'I':
          colorForCurrentStation = CRGB(253, 0, 0);
          break;

        case 'L':
          colorForCurrentStation = CRGB(251, 63, 255);
          break;

        default:
          colorForCurrentStation = CRGB(255, 255, 0);
        }

        // ledStrip.setLedColor(i, colorForCurrentStation);
        leds[i] = colorForCurrentStation;
        Serial.println("Setting " + metarStations[j].stationName + " LED # " + metarStations[j].ledNumber + " to " + metarStations[j].weather);
        ledWeatherSet = true;
        break;
      }
    }

    if (!ledWeatherSet)
    {
      // ledStrip.setLedColor(i, OFF_COLOR);
      leds[i] = CRGB(0, 0, 0);
      Serial.println("Setting LED # " + String(i) + " to OFF");
    }
    ledStrip.apply();
  }
}