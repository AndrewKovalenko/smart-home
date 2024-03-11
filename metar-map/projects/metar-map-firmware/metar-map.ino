// requires STRICTLY FastLed 3.2.10
#include <Arduino.h>
#include <EEPROM.h>
#include "src/settingsStorage/crc16.h"
#include "src/configuration.h"
#include "src/boardModeManager/boardManager.h"

#define BOARD_BAUD 115200
// Seattle TAC URL example
// https://www.aviationweather.gov/adds/dataserver_current/httpparam?datasource=metars&requestType=retrieve&format=csv&mostRecentForEachStation=constraint&hoursBeforeNow=1.25&stationString=%20KEAT%20KENL%20KSMP%20KPLU%20KRNT%20KBFI%20KSEA%20KTIW%20KTCM%20KGRF%20KPWT%20KOLM%20KSHN%20KHQM%20KUIL%20KCLM%20CYYJ%20KFHR%20KORS%20KBLI%20KBVS%20KNUW%20K0S9%20KPAE%20KAWO%20KS52
// JSON data from new API
// https://beta.aviationweather.gov/cgi-bin/data/metar.php?format=json&ids=KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52
// Box region url
// https://aviationweather.gov/cgi-bin/json/MetarJSON.php?zoom=7&filter=prior&density=0&taf=0&bbox=-125.89991621094,44.800119886377,-114.85865644532,49.468498047905
// http://192.168.0.55:8000/getFlightCategory/KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52
// https://metar-map.azurewebsites.net/api/get_flight_category?stations=KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52
BoardManager boardManager = BoardManager(WEATHER_URL_BASE);
const uint32_t WEATHER_REFRESH_RATE = 1000 * 60 * 15; // 15 minutess

void setup()
{
  Serial.println(" ------------- BEGIN Setup -------------");
  Serial.begin(BOARD_BAUD);
  Serial.println();

  if (boardManager.boardMode() == WeatherClient)
  {
    Serial.println("Read weather");
    boardManager.connectToWiFiNetwork();
  }
  else
  {
    Serial.println("Setup wifi");
    boardManager.startInWiFiSetupMode();
  }
  Serial.println("------------- END Setup -------------");
}

void loop()
{
  Serial.println("------------- BEGIN Loop -------------");
  if (boardManager.boardMode() == WeatherClient)
  {
    boardManager.displayWeatherOnTheMap();
    delay(WEATHER_REFRESH_RATE);
  }
  else
  {
    boardManager.handleHttpClient();
  }
  Serial.println("-------------- END Loop -------------");
}
