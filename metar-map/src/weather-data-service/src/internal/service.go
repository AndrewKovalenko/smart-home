package internal

import (
	"encoding/json"
	"errors"
	"fmt"
	"weatherdataservice/internal/models"
	"weatherdataservice/internal/repositories"
)

const stationNameProperty = "id"
const flightCategoryProperty = "fltcat"
const undefinedFlightCategory = "undefined"

func parseWeatherData(response []byte) (map[string]string, error) {
	var weatherData models.AviationWeatherAPIResponse
	parsingError := json.Unmarshal(response, &weatherData)

	if parsingError != nil {
		return nil, errors.New("unable to parse aw response")
	}

	result := make(map[string]string)

	for _, stationData := range weatherData.StationsData {
		stationName, stationNamePresent := stationData.Properties[stationNameProperty]

		stationNameString := fmt.Sprintf("%v", stationName)
		if !stationNamePresent {
			continue
		}

		flightCategory, flightCategoryPresent := stationData.Properties[flightCategoryProperty]

		if !flightCategoryPresent {
			flightCategory = undefinedFlightCategory
		}

		result[stationNameString] = fmt.Sprintf("%v", flightCategory)
	}

	return result, nil
}

func extractCategoriesForRequestedStations(
	flightCategories map[string]string,
	requestedStations []string,
	stationOverrides map[string]string,
) ([]models.StationFlightCategory, error) {
	result := make([]models.StationFlightCategory, 0)

	for _, stationName := range requestedStations {
		var categoryToUse string

		if reportedCategory, categoryExist := flightCategories[stationName]; categoryExist {
			categoryToUse = reportedCategory
		} else {
			categoryToUse = undefinedFlightCategory
		}

		if overrideStation, overrideExist := stationOverrides[stationName]; overrideExist {
			if overrideStationCategory, recordExists := flightCategories[overrideStation]; recordExists {
				categoryToUse = overrideStationCategory
			} else {
				categoryToUse = undefinedFlightCategory
			}
		}

		stationFlightCategoryModel := models.StationFlightCategory{
			StationId:      stationName,
			FlightCategory: categoryToUse,
		}

		result = append(result, stationFlightCategoryModel)
	}

	return result, nil
}

func GetWeather(requestedStations []string) ([]models.StationFlightCategory, error) {
	metars, err := repositories.GetMetarsForStations(requestedStations)

	if err != nil {
		return nil, err
	}

	flightCategories, err := parseWeatherData(response)

	if err != nil {
		return nil, err
	}

	serviceConfig, err := repositories.GetServiceConfig()

	if err != nil {
		return extractCategoriesForRequestedStations(flightCategories, requestedStations, nil)
	}

	return extractCategoriesForRequestedStations(
		flightCategories,
		requestedStations,
		serviceConfig.StationOverrides,
	)
}
