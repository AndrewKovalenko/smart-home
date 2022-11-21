package internal

import (
	"strings"
	"testing"
)

var stationsToCheckString = "KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52"

func contains(sl []string, name string) bool {
	for _, value := range sl {
		if value == name {
			return true
		}
	}
	return false
}

func TestWeatherServiceParsesResponseProperly(t *testing.T) {
	stationsToCheck := strings.Split(stationsToCheckString, ",")
	stationsFlightCategories, err := parseWeatherData([]byte(testResponse))

	if err != nil {
		t.Error(err)
	}

	if len(stationsToCheck) != len(stationsFlightCategories) {
		t.Error("not all stations were found")
	}

	for _, stationData := range stationsFlightCategories {
		if !contains(stationsToCheck, stationData.StationId) {
			t.Errorf("station data for %s is missing", stationData.StationId)
		}

		if stationData.FlightCategory == undefinedFlightCategory {
			t.Errorf("no flight cathegory for station %s", stationData.StationId)
		}
	}

	t.Log("Passed parsing test")
}
