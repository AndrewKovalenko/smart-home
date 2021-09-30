import parse 

WEATHER_SOURCE_URL = 'https://www.aviationweather.gov/adds/dataserver_current/httpparam?datasource=metars&requestType=retrieve&format=csv&mostRecentForEachStation=constraint&hoursBeforeNow=1.25&stationString='

WEATHER_STATIONS = [
    'KPAE',
    'KAWO',
    'KRNT',
    'KPWT'
]

def getWeatherSourceUrl():
    stations = ''

    for station in WEATHER_STATIONS:
        stations += station + ' '

    encodedStations = parse.quote(stations.strip())
    return WEATHER_SOURCE_URL + encodedStations
    
