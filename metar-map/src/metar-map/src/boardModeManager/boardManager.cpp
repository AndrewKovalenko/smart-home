#include <ESP8266WiFi.h>
#include "../weather/weatherColorCodes.h"
#include "../httpClient/http-client.h"
#include "../weather/weatherDataRetriever.h"
#include "../weather/weatherStation.h"
#include "../wifiAccessPoint/accessPoint.h"
#include "../wifiAccessPoint/configurationHttpServer.h"
#include "boardManager.h"
#include "stationsToLedsMapping.h"
// #include <FastLED.h>

#define NUM_LEDS 50
// CRGB leds[NUM_LEDS];

#define WIFI_RECONNECT_DELAY 1000
#define MAX_CONNECTION_ATTEMPTS 15
#define LED_DATA_PIN 5

BoardManager::BoardManager(String baseUrl)
{
  weatherReadingUrl = buildWeatherRetrievingUrl(baseUrl, metarStations, NUMBER_OF_STATIONS);
  httpServer = NULL;
  // ledStrip = WS2811LedStrip();
  _credentials = readWifiCredentials();
  _boardMode = areCredentialsBlank(_credentials) ? WiFiSetup : WeatherClient;
}

WiFiCredentials BoardManager::getWifiCredentials()
{
  WiFiCredentials credentialsSaved = readWifiCredentials();
  Serial.println(credentialsSaved.ssid);
  Serial.println(credentialsSaved.password);
  return credentialsSaved;
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
  WiFiCredentials savedCredentials = readWifiCredentials();
  WiFi.begin(savedCredentials.ssid, savedCredentials.password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(WIFI_RECONNECT_DELAY);
    Serial.print(".");
    connectionAttempts++;

    if (connectionAttempts > MAX_CONNECTION_ATTEMPTS)
    {
      resetCredentialsStorage();
      ESP.restart();
    }
  }

  // FastLED.addLeds<WS2811, 3, RGB>(leds, NUM_LEDS);
}

void BoardManager::displayWeatherOnTheMap()
{
  // for (uint8_t i = 0; i < NUM_LEDS; i++)
  // {
  //   leds[i] = CRGB::Black;
  //   Serial.println("Setting led " + String(i) + " to black");
  // }
  // FastLED.show();

  // for (uint8_t i = 0; i < NUM_LEDS; i++)
  // {
  //   leds[i] = CRGB::Red;
  //   FastLED.show();
  //   Serial.println("Setting led " + String(i) + " to red");
  //   delay(500);
  // }
  // CRGBArray<50> leds;
  // FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, 50);
  // FastLED.setBrightness(60);
  // Serial.println("Weather URL: " + weatherReadingUrl);
  // String weatherDataJson = makeGetCall(weatherReadingUrl);
  // const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));
  // Serial.println("Response");
  // Serial.println(weatherDataJson);
  // parseResponse(weatherDataJson, metarStations, numberOfStations);

  // for (uint8_t i = 0; i < 50; i++)
  // {
  //   bool ledSet = false;

  //   for (uint8_t j = 0; j < numberOfStations; j++)
  //   {
  //     if (i == metarStations[j].ledNumber)
  //     {
  //       LedColor colorForCurrentStation;

  //       switch (metarStations[j].weather[0])
  //       {
  //       case 'V':
  //         Serial.println("Setting " + String(i) + " to VFR");
  //         colorForCurrentStation = VFR_COLOR;
  //         break;

  //       case 'M':
  //         Serial.println("Setting " + String(i) + " to MVFR");
  //         colorForCurrentStation = MVFR_COLOR;
  //         break;

  //       case 'I':
  //         Serial.println("Setting " + String(i) + " to IFR");
  //         colorForCurrentStation = IFR_COLOR;
  //         break;

  //       case 'L':
  //         Serial.println("Setting " + String(i) + " to LIFR");
  //         colorForCurrentStation = LIFR_COLOR;
  //         break;

  //       default:
  //         Serial.println("Setting " + String(i) + " to ERROR");
  //         colorForCurrentStation = NO_DATA_COLOR;
  //       }

  //       ledStrip.setLedColor(i, colorForCurrentStation);
  //       ledSet = true;
  //       break;
  //     }
  //   }

  //   if (!ledSet)
  //   {
  //     Serial.println("Setting " + String(i) + " to OFF");
  //     ledStrip.setLedColor(i, OFF_COLOR);
  //   }

  //   Serial.println("Applying");
  //   ledStrip.apply();
  // }

  // for (uint8_t i = 0; i < 50; i++)
  // {
  //   bool ledSet = false;

  //   for (uint8_t j = 0; j < 26; j++)
  //   {
  //     if (i == metarStations[j].ledNumber)
  //     {
  //       CRGB colorForCurrentStation;
  //       switch (metarStations[j].weather[0])
  //       {
  //       case 'V':
  //         Serial.println("Setting " + String(i) + " to VFR");
  //         colorForCurrentStation = CRGB(34, 197, 1);
  //         break;

  //       case 'M':
  //         Serial.println("Setting " + String(i) + " to MVFR");
  //         colorForCurrentStation = CRGB(31, 112, 219);
  //         break;

  //       case 'I':
  //         Serial.println("Setting " + String(i) + " to IFR");
  //         colorForCurrentStation = CRGB(253, 0, 0);
  //         break;

  //       case 'L':
  //         Serial.println("Setting " + String(i) + " to LIFR");
  //         colorForCurrentStation = CRGB(251, 63, 255);
  //         break;

  //       default:
  //         Serial.println("Setting " + String(i) + " to ERROR");
  //         colorForCurrentStation = CRGB(255, 255, 0);
  //       }
  //       leds[i] = colorForCurrentStation;
  //       ledSet = true;
  //       break;
  //     }
  //   }

  //   if (!ledSet)
  //   {
  //     Serial.println("Setting " + String(i) + " to OFF");
  //     leds[i] = CRGB(0, 0, 0);
  //   }

  //   FastLED.show();
  // }
}