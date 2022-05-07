#include <Arduino.h>
#define WEATHER_URL_BASE "https://www.aviationweather.gov/adds/dataserver_current/httpparam?datasource=metars&requestType=retrieve&format=csv&mostRecentForEachStation=constraint&hoursBeforeNow=1.25&stationString="

#include "src/boardModeManager/boardManager.h"

#define BOARD_BAUD 115200

WS2811LedStrip ledStrip;
BoardMode mode = WiFiSetup;

// const uint32_t WEATHER_REFRESH_RATE = 1000 * 60 * 15; // 15 minutess
// const char *ssid = "BrainBurner";
// const char *password = "Sw6%H0mE!";
// String weatherUrl;
// const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));

void setup()
{
  Serial.begin(BOARD_BAUD);

  mode = readMode();

  if (mode == WeatherClient)
  {
    connectToWiFiNetwork(WEATHER_URL_BASE);
  }
}

void loop()
{
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
