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
    uint16_t crc = calculateCRC(credentials.ssid + credentials.password);
    return crc != credentials.crc;
}

void saveWiFiCredentials(WiFiCredentials credentials)
{
    credentials.crc = calculateCRC(credentials.ssid + credentials.password);
    EEPROM.begin(sizeof(WiFiCredentials));
    EEPROM.put(EEPROM_CREDENTIALS_ADDRESS, credentials);
    EEPROM.end();
}

WiFiCredentials readWifiCredentials()
{
    WiFiCredentials credentials;

    EEPROM.begin(sizeof(WiFiCredentials));
    EEPROM.get(EEPROM_CREDENTIALS_ADDRESS, credentials);
    EEPROM.end();

    return credentials;
}

void resetCredentialsStorage()
{
    WiFiCredentials credentials;

    credentials.crc = 0;
    credentials.ssid = BLANK;
    credentials.password = BLANK;

    EEPROM.begin(sizeof(WiFiCredentials));
    EEPROM.put(EEPROM_CREDENTIALS_ADDRESS, credentials);
    EEPROM.end();
}
