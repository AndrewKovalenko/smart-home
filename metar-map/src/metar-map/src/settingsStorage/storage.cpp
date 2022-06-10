#include "storage.h"

const uint8_t EEPROM_CREDENTIALS_ADDRESS = 0;
const char BLANK[] = "BLANK";

uint16_t calculateCRC(String str)
{
    uint16_t crc = 0;
    for (int i = 0; i < str.length(); i++)
    {
        crc = _crc16_update(crc, str[i]);
    }
    return crc;
}

bool areCredentialsBlank(WiFiCredentials credentials)
{
    uint16_t crc = calculateCRC(String(credentials.ssid) + String(credentials.password));
    return crc != credentials.crc;
}

void saveWiFiCredentials(WiFiCredentials credentials)
{
  EEPROM.begin(READ_BUFFER_SIZE);
  credentials.crc = calculateCRC(String(credentials.ssid) + String(credentials.password));

  EEPROM.put(EEPROM_CREDENTIALS_ADDRESS, credentials);

  EEPROM.commit();
  EEPROM.end();  

    Serial.println("Saving SSID: " + String(credentials.ssid));
    Serial.println("Saving Password: " + String(credentials.password));
    Serial.println("Saving Crc: " + String(credentials.crc));
}

WiFiCredentials* readWifiCredentials()
{
    Serial.println("Reading credentials");
    WiFiCredentials* credentials = new WiFiCredentials();
    Serial.println("Allocated memory");

    EEPROM.begin(READ_BUFFER_SIZE);
    Serial.println("Allocated buffer");
    EEPROM.get(EEPROM_CREDENTIALS_ADDRESS, *credentials);
    Serial.println("Read credentials");
    EEPROM.end();
    Serial.println("Freed buffer");

    return credentials;
}

void resetCredentialsStorage()
{
    WiFiCredentials credentials;

    credentials.crc = 0;
    strcpy(credentials.ssid, BLANK);
    strcpy(credentials.password, BLANK);

    EEPROM.begin(READ_BUFFER_SIZE);
    EEPROM.put(EEPROM_CREDENTIALS_ADDRESS, credentials);
    EEPROM.commit();
    EEPROM.end();
}
