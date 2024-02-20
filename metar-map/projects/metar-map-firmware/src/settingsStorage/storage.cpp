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
}

WiFiCredentials readWifiCredentials()
{
    WiFiCredentials credentials;
    EEPROM.begin(READ_BUFFER_SIZE);
    EEPROM.get(EEPROM_CREDENTIALS_ADDRESS, credentials);
    EEPROM.end();

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
