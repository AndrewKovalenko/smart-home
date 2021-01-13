#include <EEPROM.h>

const uint EEPROM_CREDENTIALS_ADDRESS = 0;
struct WiFiCredentials
{
    String ssid = "";
    String password = "";
};

void saveWiFiCredentials(WiFiCredentials credentials)
{
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
