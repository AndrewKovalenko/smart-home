import ure
from repositories.weathersourceconfig import WEATHER_STATIONS
import urequests

class WeatherRepository:
    __STARION_SEPARATOR = '%20'
    __RESPONSE_ROW_SEPARATOR = '\n'

    __AIRPORT_DATA_ROW_REGEX = ure.compile(r"^(K[A-Z][A-Z][A-Z]|[A-Z\d][A-Z\d][A-Z\d])\s")
    __AIRPORT_CODE_INDEX = 1
    __WEATHER_SATUS_INDEX = 30

    def __init__(self, stations, weatherSourceUrl) -> None:
        self.__requestWeatherDataUrl = self.__buildWeatherDataRequestUrl(weatherSourceUrl, stations)

    def __buildWeatherDataRequestUrl(self, weatherSourceUrl, stations) -> str:
        stationsParameterValue = self.__STARION_SEPARATOR.join(stations)
        return weatherSourceUrl + stationsParameterValue

    def __parseWeatherData(self, data):
        airportStatuses = {}
        rows = data.split(self.__RESPONSE_ROW_SEPARATOR)

        for row in rows:
            march = self.__AIRPORT_DATA_ROW_REGEX.search(row.strip())
            if march is not None:
                metarParameters = row.split(',')
                airportStatuses[metarParameters[self.__AIRPORT_CODE_INDEX]] = \
                    metarParameters[self.__WEATHER_SATUS_INDEX]
        
        return airportStatuses

    #TODO: handle errors requesting data
    def getWeatherData(self):
        response = urequests.get(self.__requestWeatherDataUrl)

        return self.__parseWeatherData(response.text)
