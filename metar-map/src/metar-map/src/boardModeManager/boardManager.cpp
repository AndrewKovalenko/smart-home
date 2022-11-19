#include <ESP8266WiFi.h>
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
#include <FastLED.h>

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
  Serial.println(credentialsSaved->ssid);
  Serial.println(credentialsSaved->password);

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
  CRGBArray<50> leds;
  FastLED.addLeds<WS2811, 5>(leds, 50);
  FastLED.setBrightness(60);
  Serial.println("Weather URL: " + weatherReadingUrl);
  String weatherDataJson = makeGetCall(weatherReadingUrl);
  const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));
  parseResponse(weatherDataJson, metarStations, numberOfStations);

  for (uint8_t i = 0; i < 50; i++)
  {
    //   bool ledSet = false;

    //   for (uint8_t j = 0; j < numberOfStations; j++)
    //   {
    //     if (i == metarStations[j].ledNumber)
    //     {
    //       LedColor colorForCurrentStation;

    //       switch (metarStations[j].weather[0])
    //       {
    //       case 'V':
    //         colorForCurrentStation = VFR_COLOR;
    //         break;

    //       case 'M':
    //         colorForCurrentStation = MVFR_COLOR;
    //         break;

    //       case 'I':
    //         colorForCurrentStation = IFR_COLOR;
    //         break;

    //       case 'L':
    //         colorForCurrentStation = LIFR_COLOR;
    //         break;

    //       default:
    //         colorForCurrentStation = NO_DATA_COLOR;
    //       }

    //       ledStrip.setLedColor(i, colorForCurrentStation);
    //       ledSet = true;
    //       break;
    //     }
    //   }

    //   if (!ledSet)
    //   {
    // ledStrip.setLedColor(i, OFF_COLOR);
    //   }
  }
  // ledStrip.apply();

  for (uint8_t i = 0; i < 50; i++)
  {
    bool ledSet = false;

    for (uint8_t j = 0; j < 26; j++)
    {
      if (i == metarStations[j].ledNumber)
      {
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
        leds[i] = colorForCurrentStation;
        ledSet = true;
        break;
      }
    }

    if (!ledSet)
    {
      leds[i] = CRGB(0, 0, 0);
    }

    FastLED.show();
  }
}