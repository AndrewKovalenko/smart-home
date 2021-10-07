import ure
import urequests

class WeatherRepository:
    __MAX_STATIONS_IN_REQUEST = 15
    __STARION_SEPARATOR = '%20'
    __RESPONSE_ROW_SEPARATOR = '\n'

    __AIRPORT_DATA_ROW_REGEX = ure.compile(r"^([KC]\w\w\w)\s")
    __AIRPORT_CODE_INDEX = 1
    __WEATHER_SATUS_INDEX = 30

    def __init__(self, stations, weatherSourceUrl) -> None:
        chunk_number = 0
        stationChunks = []

        while True:
            startElement = chunk_number * self.__MAX_STATIONS_IN_REQUEST
            endElement = (chunk_number + 1) * self.__MAX_STATIONS_IN_REQUEST

            stationsChunk = stations[startElement:endElement]
            chunk_number += 1
            stationChunks.append(stationsChunk)

            if len(stations) <= chunk_number*self.__MAX_STATIONS_IN_REQUEST:
                break

        self.__requestWeatherDataUrls = []
        for chunk in stationChunks:
            self.__requestWeatherDataUrls.append(self.__buildWeatherDataRequestUrl(weatherSourceUrl, chunk))

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
        weatherForStations = {}

        for url in self.__requestWeatherDataUrls:
            print('Weather request: ', url)
            response = urequests.get(url)
            weatherForChunk = self.__parseWeatherData(response.text)
            weatherForStations.update(weatherForChunk)

        return weatherForStations
