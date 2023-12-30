package repositories

import (
	"fmt"
	"strings"
	"testing"
)

const stationsToCheckString = "KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52"

func missing(a, b []string) []string {
	result := []string{}

	ma := make(map[string]bool, len(a))
	for _, ka := range a {
		ma[ka] = true
	}
	for _, kb := range b {
		if !ma[kb] {
			result = append(result, kb)
		}
	}
	return result
}

func TestWeatherDataServerRequest(t *testing.T) {
	stations := strings.Split(stationsToCheckString, ",")
	weatherData, err := getMetarData(stations)

	if err != nil {
		t.Error("Aviation Weather Data Server request failed")
	}

	if len(weatherData) != len(stations) {
		stationsWithData := make([]string, len(weatherData))

		for i, metar := range weatherData {
			stationsWithData[i] = metar.StationId
		}

		missingStations := missing(stationsWithData, stations)
		missingStationsString := strings.Join(missingStations, ",")

		t.Error(fmt.Sprintf("Aviation Weather DataServer returned inconsistent data. \r\n Missing stations: %s", missingStationsString))
	}
}
