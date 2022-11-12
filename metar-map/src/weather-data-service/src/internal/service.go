package internal

import (
	"encoding/json"
	"errors"
	"io/ioutil"
	"net/http"
	"strings"
	"weatherdataservice/internal/models"
)

const baseWeatherDataUrl = "https://beta.aviationweather.gov/cgi-bin/data/metar.php?format=json&ids="

func GetWeather(stations []string) ([]models.StationFlightCategory, error) {
	stationQueryparamter := strings.Join(stations, ",")
	weatherDataRequestUrl := baseWeatherDataUrl + stationQueryparamter

	response, err := http.Get(weatherDataRequestUrl)

	if err != nil {
		return nil, errors.New("unable to recive weaterh data from aw api")
	}

	defer response.Body.Close()

	body, err := ioutil.ReadAll(response.Body)

	if err != nil {
		return nil, errors.New("unabel to read aw data response")
	}

	var weatherData AviationWeatherAPIResponse
	err := json.Unmarshal(body, &weatherData)

	if err != nil {
		return nil, errors.New("unable to parse aw response")
	}

	return nil, nil
}
