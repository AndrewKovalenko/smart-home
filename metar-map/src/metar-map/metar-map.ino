#include <Arduino.h>
#include <EEPROM.h>
#include "src/settingsStorage/crc16.h"
 #include "src/configuration.h"
 #include "src/boardModeManager/boardManager.h"
// #include "src/wifiAccessPoint/accessPointSettings.h"

#define BOARD_BAUD 115200
#define ADDR 0

BoardManager boardManager = BoardManager(WEATHER_URL_BASE);

const uint32_t WEATHER_REFRESH_RATE = 1000 * 60 * 15; // 15 minutess

void setup()
{
  Serial.begin(BOARD_BAUD);
  Serial.println();

  if(boardManager.readMode() == WeatherClient) 
  {
    boardManager.connectToWiFiNetwork();
    Serial.println("Starting weather client");
  }
  else
  {
    boardManager.startInWiFiSetupMode();
    Serial.println("Starting setup server");
  }


}

void loop()
{
  if (boardManager.boardMode() == WeatherClient) 
  {
    boardManager.displayWeatherOnTheMap();
    delay(WEATHER_REFRESH_RATE);
  } 
  else
  {
    boardManager.handleHttpClient();
  }


}
