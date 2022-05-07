#include <ESP8266WiFi.h>
#include "../utils/stringUtils.h"
#include "../ledController/ws2811.h"
#include "../weather/weatherColorCodes.h"
#include "../httpClient/http-client.h"
#include "../weather/weatherDataRetriever.h"
#include "../settingsStorage/storage.h"
#include "../settingsStorage/storage.h"
#include "../weather/weatherStation.h"

enum BoardMode {
  WeatherClient, 
  WiFiSetup
};

BoardMode readMode();
void startInWeatherClientMode();
void startInWiFiSetupMode();

void connectToWiFiNetwork(String baseUrl);