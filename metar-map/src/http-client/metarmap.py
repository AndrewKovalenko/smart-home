from weatherdatetransport import WeatherDataTransport
import networkcredentials as networkCredentialsRepository

class WeatherMapHttpServer:
    def __init__(self):
        wifiCredentials = networkCredentialsRepository.readNetworkCredentials()
        self.__weatherDataTransport = WeatherDataTransport(wifiCredentials['ssid'], 
            wifiCredentials['password'])
    
    def start(self):
        self.__weatherDataTransport.getWeatherData()