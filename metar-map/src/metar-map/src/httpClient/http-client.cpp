#include "http-client.h"

uint8_t countLines(String text, char lineSeparator)
{
  uint8_t result = 0;

  for(uint8_t i = 0; i < text.length; i++)
  {
    if(text[i] == lineSeparator) 
    {
      result++;
    }
  }

  return result;
}

void parseResponse(String response, String (&metars)[]) 
{
  const char separatorCode = 10;
  uint8_t linesInResponse = countLines(response, separatorCode);
  uint8_t metarsCount = 0;
  String responseLines[linesInResponse];

  split(response, separatorCode, responseLines);

  for (uint8_t i = 0; i < linesInResponse; i++)
  {
    if (responseLines[i][0] == 'K' || responseLines[i][0] == 'C') 
    {
      metars[metarsCount] = responseLines[i];
      metarsCount++;
    }
  }
}

String makeGetCall(String url)
{
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  String result;

  client->setInsecure();

  HTTPClient https;

  Serial.print("[HTTPS] begin...\n");
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

