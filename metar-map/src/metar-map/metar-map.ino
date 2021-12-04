#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "src/utils/stringUtils.h"
#include "src/ledController/ws2811.h"
#include "src/weather/weatherColorCodes.h"
#include "src/httpClient/http-client.h"
#include "src/weather/weatherDataRetriever.h"

WS2811LedStrip ledStrip;

const char* ssid     = "BrainBurner";
const char* password = "Sw6%H0mE!";
String weatherUrl;
const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));

void setup()
{
  Serial.begin(115200);
  weatherUrl = buildWeatherRetrievingUrl(
    "https://www.aviationweather.gov/adds/dataserver_current/httpparam?datasource=metars&requestType=retrieve&format=csv&mostRecentForEachStation=constraint&hoursBeforeNow=1.25&stationString=",
    metarStations,
    numberOfStations
  );

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop()
{
    Serial.println(weatherUrl);
    String result = makeGetCall(weatherUrl);
    Serial.println("Number of stations");
    Serial.println(numberOfStations);
    StationWeather response[numberOfStations];
    parseResponse(result, response);

    for (uint8_t i = 0; i < numberOfStations; i++)
    {
      Serial.println(response[i].stationName + " " + response[i].weather);
    }
    
    // Serial.println("Result recieved");
    // Serial.println(*response);

    // delay(1000 * 60 * 5); // 5 min
    delay(1000 * 5); // 5 sec
//  for (uint8_t i = 1; i <= 50; i++)
//  {
//    ledStrip.setLedColor(i, LIFR);
//  }

//  for (uint8_t i = 1; i <= 50; i++)
//  {
//    ledStrip.setLedColor(i, IFR);
//  }

//  for (uint8_t i = 1; i <= 50; i++)
//  {
//    ledStrip.setLedColor(i, MVFR);
//  }

//  for (uint8_t i = 1; i <= 50; i++)
//  {
//    ledStrip.setLedColor(i, VFR);
//  }
}
