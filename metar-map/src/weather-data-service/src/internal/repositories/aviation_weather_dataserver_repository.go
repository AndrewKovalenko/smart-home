package repositories

import (
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"net/http"
	"strconv"
	"strings"
	"unicode/utf8"
	"weatherdataservice/internal/models"
)

const metarServerUrlTemplate = "https://aviationweather.gov/api/data/metar?ids=%s&format=json&hours=0"

const broken = "BCN"
const overcast = "OVC"
const unrestrictedVisibility = "10+"

const UnknownVisibility = -1

const maxVisibility = 10

type cloudLayer struct {
	Type         string `json:"cover"`
	BaseAltitude uint   `json:"base"`
}

type weatherDataServerResponse struct {
	StationId  string          `json:"icaoId"`
	Visibility json.RawMessage `json:"visib"`
	Clouds     []cloudLayer    `json:"clouds"`
}

func getStationsFromMetars(metars []weatherDataServerResponse) []string {
	stationIds := make([]string, len(metars))

	for i, metar := range metars {
		stationIds[i] = metar.StationId
	}

	return stationIds
}

func missingStations(received, requested []string) []string {
	result := []string{}

	receivedStationSet := make(map[string]bool, len(received))
	for _, receivedStationId := range requested {
		receivedStationSet[receivedStationId] = true
	}

	for _, requestedStationId := range requested {
		if !receivedStationSet[requestedStationId] {
			result = append(result, requestedStationId)
		}
	}
	return result
}

func getMetarData(stations []string) ([]weatherDataServerResponse, error) {
	dataServerUrl := fmt.Sprintf(metarServerUrlTemplate, strings.Join(stations, ","))
	response, err := http.Get(dataServerUrl)
	result := make([]weatherDataServerResponse, len(stations))

	if err != nil {
		return result, errors.New("unable to receive weather data from aw api")
	}

	defer response.Body.Close()

	body, err := io.ReadAll(response.Body)

	if err != nil {
		return result, errors.New("unable to read aw data response")
	}

	if err := json.Unmarshal(body, &result); err != nil {
		return result, errors.New("error parsing data server response")
	}

	return result, nil
}

func extractCloudLayers(clouds []cloudLayer) []uint {
	result := []uint{}

	for _, cloudLayerData := range clouds {
		if cloudLayerData.Type == broken || cloudLayerData.Type == overcast {
			result = append(result, cloudLayerData.BaseAltitude)
		}
	}

	return result
}

func parseVisibility(rawJsonVisibilityData json.RawMessage) int {
	if utf8.Valid(rawJsonVisibilityData) {
		stringifiedVisibility := string(rawJsonVisibilityData)

		if strings.Contains(stringifiedVisibility, unrestrictedVisibility) {
			return maxVisibility
		}

		visibilityValue, err := strconv.Atoi(stringifiedVisibility)

		if err != nil {
			return UnknownVisibility
		}

		return visibilityValue
	}

	return maxVisibility
}

func GetMetarsForStations(stations []string) ([]models.Metar, error) {
	metarData, err := getMetarData(stations)

	result := make([]models.Metar, len(stations))

	if err != nil {
		return result, err
	}

	for i, metar := range metarData {
		result[i].StationId = metar.StationId
		result[i].CloudLayers = extractCloudLayers(metar.Clouds)
		result[i].Visibility = parseVisibility(metar.Visibility)
	}

	if len(stations) != len(metarData) {
		stationIdsReceived := getStationsFromMetars(metarData)
		stationsMissingData := missingStations(stationIdsReceived, stations)
		firstUnfilledStationIndex := len(metarData)

		for i, stationId := range stationsMissingData {
			unfilledItemIndex := firstUnfilledStationIndex + i
			result[unfilledItemIndex].StationId = stationId
			result[unfilledItemIndex].Visibility = UnknownVisibility
			result[unfilledItemIndex].CloudLayers = []uint{}
		}

	}

	return result, nil
}
