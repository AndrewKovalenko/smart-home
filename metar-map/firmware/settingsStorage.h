#include <EEPROM.h>

#define EEPROM_CREDENTIALS_ADDRESS 0

struct WiFiCredentials
{
    char ssid[20] = "";
    char password[20] = "";
};

void save(WiFiCredentials credentials)
{
    EEPROM.begin(sizeof(WiFiCredentials));
    EEPROM.put(EEPROM_CREDENTIALS_ADDRESS, credentials);
    EEPROM.end();
}

WiFiCredentials readCredentials()
{
    WiFiCredentials credentials;

    EEPROM.begin(sizeof(WiFiCredentials));
    EEPROM.get(EEPROM_CREDENTIALS_ADDRESS, credentials);
    EEPROM.end();

    return credentials;
}