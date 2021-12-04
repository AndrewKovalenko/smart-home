#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "src/utils/stringUtils.h"
#include "src/ledController/ws2811.h"
#include "src/weather/weatherColorCodes.h"
#include "src/httpClient/http-client.h"
#include "src/weather/weatherDataRetriever.h"

WS2811LedStrip ledStrip;

WeatherStation metarStations[25] = {
   {"KHQM", 1, ""},
   {"KUIL", 6, ""},
   {"KCLM", 9, ""},
   {"CYYJ", 11, ""},
   {"KFHR", 13, ""},
   {"KORS", 14, ""},
   {"KBLI", 15, ""},
   {"KBVS", 17, ""},
   {"KNUW", 18, ""},
   {"KAWO", 20, ""},
   {"K0S9", 22, ""},
   {"KPAE", 24, ""},
   {"KRNT", 26, ""},
   {"KBFI", 27, ""},
   {"KSEA", 28, ""},
   {"KPWT", 30, ""},
   {"KSHN", 32, ""},
   {"KOLM", 33, ""},
   {"KGRF", 34, ""},
   {"KTIW", 35, ""},
   {"KTCM", 36, ""},
   {"KPLU", 37, ""},
   {"KENL", 41, ""},
   {"KEAT", 43, ""},
   {"KS52", 48, ""}
}; 

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
    parseResponse(result, metarStations, numberOfStations);

    for (uint8_t i = 0; i < numberOfStations; i++)
    {
      Serial.println(metarStations[i].stationName + " " + metarStations[i].weather);

      LedColor colorForCurrentStation;

      switch (metarStations[i].weather[0])
      {
        case 'V':
          colorForCurrentStation = VFR;
          break;

        case 'M':
          colorForCurrentStation = MVFR;
          break;

        case 'I':
          colorForCurrentStation = IFR;
          break;

        case 'L':
          colorForCurrentStation = LIFR;
          break;

        default:
          colorForCurrentStation = NO_DATA;
      }

      ledStrip.setLedColor(i, colorForCurrentStation);
    }
    
    delay(1000 * 5); // 5 sec
}
