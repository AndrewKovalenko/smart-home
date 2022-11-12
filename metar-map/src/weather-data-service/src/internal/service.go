package internal

import (
	"encoding/json"
	"errors"
	"io/ioutil"
	"net/http"
	"weatherdataservice/internal/models"
)

const boxDataUrl = "https://aviationweather.gov/cgi-bin/json/MetarJSON.php?zoom=7&filter=prior&density=all&taf=0&bbox=-124.57,46.96,-120.14,48.8"
const stationNameProperty = "id"
const flightCategoryProperty = "fltcat"
const undefinedFlightCategory = "undefined"

func contains(sl []string, name string) bool {
	for _, value := range sl {
		if value == name {
			return true
		}
	}
	return false
}

func getWeatherData() ([]byte, error) {
	response, err := http.Get(boxDataUrl)

	if err != nil {
		return nil, errors.New("unable to recive weaterh data from aw api")
	}

	defer response.Body.Close()

	body, err := ioutil.ReadAll(response.Body)

	if err != nil {
		return nil, errors.New("unabel to read aw data response")
	}

	return body, nil
}

func parseWeatherData(response []byte, requestedStations []string) ([]models.StationFlightCategory, error) {
	var weatherData AviationWeatherAPIResponse
	parsingError := json.Unmarshal(response, &weatherData)

	if parsingError != nil {
		return nil, errors.New("unable to parse aw response")
	}

	result := make([]models.StationFlightCategory, len(requestedStations))

	for _, stationData := range weatherData.StationsData {
		stationName, stationNamePresent := stationData.Properties[stationNameProperty]

		if !stationNamePresent || !contains(requestedStations, stationName) {
			continue
		}

		flightCategory, flightCategoryPresent := stationData.Properties[flightCategoryProperty]

		if !flightCategoryPresent {
			flightCategory = undefinedFlightCategory
		}

		weatherStation := models.StationFlightCategory{
			StationId:      stationName,
			FlightCategory: flightCategory,
		}

		result = append(result, weatherStation)
	}

	return result, nil
}

func GetWeather(requestedStations []string) ([]models.StationFlightCategory, error) {
	response, err := getWeatherData()

	if err != nil {
		return nil, err
	}

	return parseWeatherData(response, requestedStations)
}
