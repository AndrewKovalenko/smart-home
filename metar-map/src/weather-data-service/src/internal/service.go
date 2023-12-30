package internal

import (
	"slices"
	"weatherdataservice/internal/models"
	"weatherdataservice/internal/repositories"
)

const LowIFR = "LIFR"
const IFR = "IFR"
const MarginalVFR = "MVFR"
const VFR = "VFR"

func determineFlightCategory(visibility int, cloudLayers []uint) string {
	lowestCloudLayerHight := slices.Min(cloudLayers)

	if lowestCloudLayerHight < 500 || visibility < 1 {
		return LowIFR
	}

	if lowestCloudLayerHight < 1000 || visibility < 3 {
		return IFR
	}

	if lowestCloudLayerHight < 3000 || visibility < 5 {
		return MarginalVFR
	}

	return VFR
}

func GetWeather(requestedStations []string) ([]models.StationFlightCategory, error) {
	metars, err := repositories.GetMetarsForStations(requestedStations)
	result := make([]models.StationFlightCategory, len(requestedStations))

	if err != nil {
		return nil, err
	}

	for i, metar := range metars {
		result[i].StationId = metar.StationId
		result[i].FlightCategory = determineFlightCategory(metar.Visibility, metar.CloudLayers)
	}

	return result, nil
}
