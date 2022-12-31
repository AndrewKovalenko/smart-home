#ifndef _BOARD_MANAGER_

#include <ESP8266WebServer.h>
// #include "../ledController/ws2811.h"

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
  BoardMode _boardMode;
  ESP8266WebServer *httpServer;

public:
  BoardManager(String);

  BoardMode readMode();
  BoardMode boardMode();

  void startInWiFiSetupMode();
  void handleHttpClient();
  void connectToWiFiNetwork();
  void displayWeatherOnTheMap();
};
#endif