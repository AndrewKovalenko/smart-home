package httphandlers

import (
	"encoding/json"
	"net/http"
	"strings"

	"weatherdataservice/internal"

	"github.com/gorilla/mux"
)

func GetStationsFlightCategory(w http.ResponseWriter, r *http.Request) {
	queryStringParams := mux.Vars(r)
	stationsParameter := queryStringParams["stations"]

	stations := strings.Split(stationsParameter, ",")
	flightCategories, err := internal.GetWeather(stations)

	w.Header().Set("Content-Type", "application/json")

	if err != nil {
		w.WriteHeader(http.StatusFailedDependency)
		w.Write([]byte("Unable to fetch flight category data"))

		return
	}

	json.NewEncoder(w).Encode(flightCategories)
}

func HealthCheck(w http.ResponseWriter, r *http.Request) {
	json.NewEncoder(w).Encode("ok")
}
