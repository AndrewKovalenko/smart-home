import ure
from repositories.weathersourceconfig import WEATHER_STATIONS
import urequests
from weathersourceconfig import getWeatherSourceUrl

APRPORT_DATA_ROW = ure.compile(r"^(K[A-Z][A-Z][A-Z]|[A-Z\d][A-Z\d][A-Z\d])\s")
AIRPORT_CODE_INDEX = 1
WEATHER_SATUS_INDEX = 30

def parseWeatherData(data):
    airportStatuses = {}

    rows = data.split('\n')

    print('rows: ', rows)

    for row in rows:
        print('looking at: ', row, '\n\r')
        march = APRPORT_DATA_ROW.search(row.strip())
        if march is not None:
            print('row ', row, ' tested positive\n\r')
            metarParameters = row.split(',')
            print(metarParameters[AIRPORT_CODE_INDEX], metarParameters[WEATHER_SATUS_INDEX])
            airportStatuses[metarParameters[AIRPORT_CODE_INDEX]] = metarParameters[WEATHER_SATUS_INDEX]
    
    return airportStatuses




def getWeatherData():
    weatherUrl = getWeatherSourceUrl()
    response = urequests.get(weatherUrl)

    return parseWeatherData(response.text)
