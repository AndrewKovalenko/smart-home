package internal

import (
	"strings"
	"testing"
)

var stationsToCheckString = "KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52"

func TestWeatherServiceParsesResponseProperly(t *testing.T) {
	stationsToCheck := strings.Split(stationsToCheckString, ",")
	stationsFlightCategories, err := parseWeatherData([]byte(testResponse), stationsToCheck)

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
