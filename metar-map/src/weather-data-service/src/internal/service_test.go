package internal

import (
	"strings"
	"testing"
)

var stationsToCheckString = "KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52"

func TestWeatherServiceParsesResponseProperly(t *testing.T) {
	stationsToCheck := strings.Split(stationsToCheckString, ",")
	stationsFlightCategories, _ := parseWeatherData([]byte(testResponse), stationsToCheck)

	for _, stationData := range stationsFlightCategories {
		if !contains(stationsToCheck, stationData.StationId) {
			t.Errorf("station data for %s is missing", stationData.StationId)
		}

		if stationData.FlightCategory == undefinedFlightCategory {
			t.Errorf("no flight cathegory for station %s", stationData.StationId)
		}
	}

	t.Log("Passed")
}
