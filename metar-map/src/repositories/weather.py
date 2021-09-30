import ure
from repositories.weathersourceconfig import WEATHER_STATIONS
import urequests
from weathersourceconfig import getWeatherSourceUrl

# No errors
# No warnings
# 4 ms
# data source=metars
# 2 results
# raw_text,station_id,observation_time,latitude,longitude,temp_c,dewpoint_c,wind_dir_degrees,wind_speed_kt,wind_gust_kt,visibility_statute_mi,altim_in_hg,sea_level_pressure_mb,corrected,auto,auto_station,maintenance_indicator_on,no_signal,lightning_sensor_off,freezing_rain_sensor_off,present_weather_sensor_off,wx_string,sky_cover,cloud_base_ft_agl,sky_cover,cloud_base_ft_agl,sky_cover,cloud_base_ft_agl,sky_cover,cloud_base_ft_agl,flight_category,three_hr_pressure_tendency_mb,maxT_c,minT_c,maxT24hr_c,minT24hr_c,precip_in,pcp3hr_in,pcp6hr_in,pcp24hr_in,snow_in,vert_vis_ft,metar_type,elevation_m
# KPAE 290253Z 08004KT 10SM SCT032 OVC046 12/09 A3007 RMK AO2 SLP184 60000 T01170094 51006,KPAE,2021-09-29T02:53:00Z,47.92,-122.28,11.7,9.4,80,4,,10.0,30.070866,1018.4,,,TRUE,,,,,,,SCT,3200,OVC,4600,,,,,VFR,0.6,,,,,,0.005,,,,,METAR,166.0
# KSEA 290253Z 20011KT 10SM BKN085 13/08 A3008 RMK AO2 SLP192 T01280078 53008,KSEA,2021-09-29T02:53:00Z,47.45,-122.32,12.8,7.8,200,11,,10.0,30.079725,1019.2,,,TRUE,,,,,,,BKN,8500,,,,,,,VFR,0.8,,,,,,,,,,,METAR,115.0

APRPORT_DATA_ROW = ure.compile(r"^K")
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
