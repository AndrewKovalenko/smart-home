#include "http-client.h"

uint8_t countLines(String text, char lineSeparator)
{
  uint8_t result = 0;
  uint textLength = text.length();

  for(uint i = 0; i < textLength; i++)
  {
    if(text[i] == lineSeparator) 
    {
      result++;
    }
  }

  return result;
}

void parseResponse(String response, WeatherStation (&metars)[], uint8_t numberOfStations) 
{
  const char separatorCode = 10;
  uint8_t linesInResponse = countLines(response, separatorCode);
  String responseLines[linesInResponse];

  split(response, separatorCode, responseLines);

  const uint8_t expectedMetarValues = 44;

  for (uint8_t i = 0; i < linesInResponse; i++)
  {
    if (responseLines[i][0] == 'K' || responseLines[i][0] == 'C') 
    {

      String metarValues[expectedMetarValues];
      split(responseLines[i], ',', metarValues);

      String stationName = metarValues[1];

      for (uint8_t j = 0; j < numberOfStations; j++)
      {
        if(metars[j].stationName == stationName) 
        {
          Serial.println(metarValues[30]);
          metars[j].weather = metarValues[30];
          break;
        }
      }
    }
  }
}

String makeGetCall(String url)
{
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  String result;

  client->setInsecure();

  HTTPClient https;

  if (https.begin(*client, url)) {  // HTTPS

    Serial.print("[HTTPS] GET...\n");
    // start connection and send HTTP header
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        result = https.getString();
      }
    } else {
      result = "[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str();
    }

    https.end();
    return result;
  } else {
    return "[HTTPS] Unable to connect\n";
  }
}

