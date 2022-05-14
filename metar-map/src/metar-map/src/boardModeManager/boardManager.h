#ifndef _BOARD_MANAGER_

#include "../ledController/ws2811.h"

#define _BOARD_MANAGER_

enum BoardMode {
  WeatherClient, 
  WiFiSetup
};

class BoardManager
{
private:
  String weatherReadingUrl;
  WS2811LedStrip ledStrip;
  BoardMode _boardMode;

  BoardMode readMode();

public:
  BoardManager(String);
  
  BoardMode boardMode();

  void startInWiFiSetupMode();
  void startHttpServer();
  void connectToWiFiNetwork();
  void displayWeatherOnTheMap();
};
#endif