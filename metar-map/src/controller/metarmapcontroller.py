import accesspoint 
import appconfig
from networksetupserver import NetworkSetupServer
import networkcredentials as networkCredentialsRepository
from host import Host
from board import reset
from weather import WeatherRepository
from weathersourceconfig import WEATHER_DATA_URL, WEATHER_STATIONS_LED_MAP

class MetarMapController:
    def startAccessPoint(self):
        accessPoint = accesspoint.AccessPoint(appconfig.ACCESS_POINT_CREDENTIALS ,appconfig.ACCESS_POINT_NETWORK)
        accessPoint.start()

        apHttpServer = NetworkSetupServer({
            'ip_address': appconfig.ACCESS_POINT_NETWORK['loacl_ip'],
            'port': appconfig.HTTP_SERVER_PORT
        })

        apHttpServer.startServer()
        print('ACCESS POINT server stoped')
        reset()

    def startMap(self):
        # networkCredentials = networkCredentialsRepository.readNetworkCredentials()
        host = Host(
            # networkCredentials['ssid'],
            # networkCredentials['password'],
            'BrainBurner',
            'Sw6%H0mE!',
            appconfig.CONNECTION_RETRIES
        )

        if not host.connect():
            # print('Cant connect to ', networkCredentials['ssid'] + '@' + networkCredentials['password'])
            # networkCredentialsRepository.whipeOutCredentials()
            print('Credentials storage cleaned out')
            # reset()
            return

        weatherDataRepository = WeatherRepository(WEATHER_STATIONS_LED_MAP.keys(), WEATHER_DATA_URL)
        weatherData = weatherDataRepository.getWeatherData()
        print(weatherData)

    def start(self):
        # if networkCredentialsRepository.areCredentialsSet():
        print('Starting controller at "MAP" mode')
        self.startMap()

        # else:
            # print('Starting controller at "ACCESS POINT" mode')
            # self.startAccessPoint()



