#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "src/utils/stringUtils.h"
#include "src/ledController/ws2811.h"
#include "src/weather/weatherColorCodes.h"
#include "src/httpClient/http-client.h"
#include "src/weather/weatherDataRetriever.h"

WS2811LedStrip ledStrip;

WeatherStation metarStations[26] = {
   {"KEAT", 0, ""},  
   {"KENL", 2, ""},  
   {"KSMP", 4, ""},  
   {"KPLU", 6, ""},  
   {"KSEA", 8, ""},  
   {"KRNT", 9, ""},  
   {"KBFI", 10, ""}, 
   {"KTIW", 11, ""}, 
   {"KTCM", 12, ""}, 
   {"KGRF", 13, ""}, 
   {"KPWT", 15, ""}, 
   {"KSHN", 17, ""}, 
   {"KOLM", 18, ""}, 
   {"KHQM", 21, ""}, 
   {"KUIL", 25, ""}, 
   {"KCLM", 28, ""}, 
   {"CYYJ", 30, ""}, 
   {"KFHR", 31, ""}, 
   {"KORS", 32, ""}, 
   {"KBLI", 33, ""}, 
   {"KBVS", 35, ""}, 
   {"KNUW", 36, ""}, 
   {"K0S9", 38, ""}, 
   {"KPAE", 40, ""}, 
   {"KAWO", 41, ""}, 
   {"KS52", 47, ""}  
}; 

const uint8_t WEATHER_REFRESH_RATE = 1000 * 60 * 15; // 15 minutess
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

      ledStrip.setLedColor(metarStations[i].ledNumber, colorForCurrentStation);
    }

    ledStrip.apply();
    
    delay(WEATHER_REFRESH_RATE); 
}
