package internal

import (
	"slices"
	"weatherdataservice/internal/models"
	"weatherdataservice/internal/repositories"
)

func determineFlightCategory(visibility int, cloudLayers []uint) string {
	if visibility == repositories.UnknownVisibility {
		return ERROR
	}

	var lowestCloudLayerHight uint
	if len(cloudLayers) > 0 {
		lowestCloudLayerHight = slices.Min(cloudLayers)
	} else {
		lowestCloudLayerHight = stratosphere
	}

	if lowestCloudLayerHight < lowIFRCeiling || visibility < lowIFRVisibility {
		return LowIFR
	}

	if lowestCloudLayerHight < ifrCeiling || visibility < ifrVisibility {
		return IFR
	}

	if lowestCloudLayerHight < marginalVFRCeiling || visibility < marginalVFRVisibility {
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
