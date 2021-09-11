WEATHER_DATA_API_ADDRESS = ''

class WeatherDataTransport:
    def __init__(self, ssid, password):
        self.__dataEndpointAddress = socket.getaddrinfo(WEATHER_DATA_API_ADDRESS, 80)[0][-1]

    def getWeatherData(self):
        try:
            connection = socket.socket()
            connection.connect(self.__dataEndpointAddress)

        finally:
            connection.close()
