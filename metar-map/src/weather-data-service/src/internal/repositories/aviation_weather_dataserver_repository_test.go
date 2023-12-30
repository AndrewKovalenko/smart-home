package repositories

import (
	"fmt"
	"strings"
	"testing"
)

const stationsToCheckString = "KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52"

func TestWeatherDataServerRequest(t *testing.T) {
	stations := strings.Split(stationsToCheckString, ",")
	weatherData, err := getMetarData(stations)

	if err != nil {
		t.Error("Aviation Weather Data Server request failed")
	}

	if len(weatherData) != len(stations) {
		stationsWithData := getStationsFromMetars(weatherData)
		missingStations := missingStations(stationsWithData, stations)
		missingStationsString := strings.Join(missingStations, ",")

		t.Error(fmt.Sprintf("Aviation Weather DataServer returned inconsistent data. \r\n Missing stations: %s", missingStationsString))
	}
}
