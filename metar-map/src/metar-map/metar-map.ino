#include <Arduino.h>

#include "src/configuration.h"
#include "src/boardModeManager/boardManager.h"
#include "src/wifiAccessPoint/accessPointSettings.h"

#define BOARD_BAUD 9600

BoardManager boardManager = BoardManager(WEATHER_URL_BASE);

const uint32_t WEATHER_REFRESH_RATE = 1000 * 60 * 15; // 15 minutess
// String weatherUrl;
// const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));

void setup()
{
  Serial.begin(BOARD_BAUD);

  if (boardManager.boardMode() == WeatherClient) 
  {
    Serial.println("Credentials set");
    boardManager.connectToWiFiNetwork();
  } else
  {
    Serial.println("Credentials NOT set");
    boardManager.startInWiFiSetupMode();
  }
}

void loop()
{
  if (boardManager.boardMode() == WeatherClient) 
  {
    Serial.println("Looping...");
  } 
  else
  {
    Serial.println("Handling http...");
    boardManager.handleHttpClient();
  }
  delay(2000);
  // if(boardManager.boardMode() == WeatherClient)
  // {
  //   boardManager.displayWeatherOnTheMap();
  //   delay(WEATHER_REFRESH_RATE);
  // } else
  // {
  //   boardManager.startHttpServer();
  // }
  // Serial.println(weatherUrl);
  // String result = makeGetCall(weatherUrl);
  // Serial.println("Number of stations");
  // Serial.println(numberOfStations);
  // parseResponse(result, metarStations, numberOfStations);

  // for (uint8_t i = 0; i < numberOfStations; i++)
  // {
  //   LedColor colorForCurrentStation;

  //   switch (metarStations[i].weather[0])
  //   {
  //   case 'V':
  //     colorForCurrentStation = VFR_COLOR;
  //     break;

  //   case 'M':
  //     colorForCurrentStation = MVFR_COLOR;
  //     break;

  //   case 'I':
  //     colorForCurrentStation = IFR_COLOR;
  //     break;

  //   case 'L':
  //     colorForCurrentStation = LIFR_COLOR;
  //     break;

  //   default:
  //     colorForCurrentStation = NO_DATA_COLOR;
  //   }

  //   Serial.println("|" + metarStations[i].stationName + "|" + metarStations[i].weather + "|");
  //   ledStrip.setLedColor(metarStations[i].ledNumber, colorForCurrentStation);
  //   ledStrip.apply();
  // }

  // delay(WEATHER_REFRESH_RATE);
}
