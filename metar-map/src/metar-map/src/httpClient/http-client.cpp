#include "http-client.h"

void parseResponse(String response, String (&responseLines)[31])
{
  const char sepratorCode = 10;
  const uint responseSize = response.length();

  Serial.print("Size of response: ");
  Serial.println(responseSize);

  uint from = 0;
  uint8_t stringCounter = 0;

  for (uint i=0; i<responseSize; i++)
  {
    if (response[i] == sepratorCode || i == responseSize - 1) {
      String responseLine = response.substring(from, i);
      responseLines[stringCounter] = responseLine;
      from = i + 1;
      stringCounter++;
    }
  }

  Serial.println("Loop has finished");
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

