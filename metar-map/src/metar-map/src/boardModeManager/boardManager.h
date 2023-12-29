#ifndef _BOARD_MANAGER_

#include <ESP8266WebServer.h>
// #include "../ledController/ws2811.h"
#include "../settingsStorage/storage.h"

#define _BOARD_MANAGER_

enum BoardMode
{
  WeatherClient,
  WiFiSetup
};

class BoardManager
{
private:
  String weatherReadingUrl;
  // WS2811LedStrip ledStrip;
  WiFiCredentials _credentials;
  BoardMode _boardMode;
  ESP8266WebServer *httpServer;

  WiFiCredentials getWifiCredentials();

public:
  BoardManager(String);

  BoardMode boardMode();

  void startInWiFiSetupMode();
  void handleHttpClient();
  void connectToWiFiNetwork();
  void displayWeatherOnTheMap();
};
#endif