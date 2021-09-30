import urequests


def getWeatherData():
    response = urequests.get('https://www.aviationweather.gov/adds/dataserver_current/httpparam?datasource=metars&requestType=retrieve&format=csv&mostRecentForEachStation=constraint&hoursBeforeNow=1.25&stationString=KPAE%20KSEA')
    return response.text
