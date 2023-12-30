package repositories

import (
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"net/http"
	"strings"
	"weatherdataservice/internal/models"
)

const metarServerUrlTemplate = "https://aviationweather.gov/api/data/metar?ids=%sE&format=json"

func GetMetarsForStations(stations []string) ([]models.WeatherDataServerResponse, error) {
	dataServerUrl := fmt.Sprintf(metarServerUrlTemplate, strings.Join(stations, ","))
	response, err := http.Get(dataServerUrl)
	result := make([]models.WeatherDataServerResponse, len(stations))

	if err != nil {
		return result, errors.New("unable to receive weather data from aw api")
	}

	defer response.Body.Close()

	body, err := io.ReadAll(response.Body)

	if err != nil {
		return result, errors.New("unable to read aw data response")
	}

	if err := json.Unmarshal(body, &result); err != nil {
		return result, errors.New("error parsing dataserver response")
	}

	return result, nil
}
