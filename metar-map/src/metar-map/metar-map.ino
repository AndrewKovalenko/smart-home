#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "src/ledController/ws2811.h"
#include "src/weather/weatherColorCodes.h"
#include "src/httpClient/http-client.h"
#include "src/weather/weatherDataRetriever.h"

WS2811LedStrip ledStrip;

const char* ssid     = "BrainBurner";
const char* password = "Sw6%H0mE!";

void setup()
{
  Serial.begin(115200);
  String URL = buildWeatherRetrievingUrl(
    "https://www.aviationweather.gov/adds/dataserver_current/httpparam?datasource=metars&requestType=retrieve&format=csv&mostRecentForEachStation=constraint&hoursBeforeNow=1.25&stationString=",
    stations
  );

  Serial.print(URL);

  // WiFi.begin(ssid, password);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  
  // String URL = "https://www.aviationweather.gov/adds/dataserver_current/httpparam?datasource=metars&requestType=retrieve&format=csv&mostRecentForEachStation=constraint&hoursBeforeNow=1.25&stationString=KHQM%20KUIL%20KCLM%20CYYJ%20KFHR%20KORS%20KBLI%20KBVS%20KNUW%20KAWO%20K0S9%20KPAE%20KRNT%20KBFI%20KSEA%20KPWT%20KSHN%20KOLM%20KGRF%20KTIW%20KTCM%20KPLU%20KENL%20KEAT%20KS52";
  // String result = makeGetCall(URL);

  // Serial.print(result);
}

void loop()
{
 for (uint8_t i = 1; i <= 50; i++)
 {
   ledStrip.setLedColor(i, LIFR);
 }

 for (uint8_t i = 1; i <= 50; i++)
 {
   ledStrip.setLedColor(i, IFR);
 }

 for (uint8_t i = 1; i <= 50; i++)
 {
   ledStrip.setLedColor(i, MVFR);
 }

 for (uint8_t i = 1; i <= 50; i++)
 {
   ledStrip.setLedColor(i, VFR);
 }
}
