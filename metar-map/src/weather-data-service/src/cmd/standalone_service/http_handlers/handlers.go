package httphandlers

import (
	"encoding/json"
	"fmt"
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

	if err != nil {
		fmt.Println("Error")
		return
	}

	for _, flightCategory := range flightCategories {
		json.NewEncoder(w).Encode(flightCategory)
	}
}

func HealthCheck(w http.ResponseWriter, r *http.Request) {
	json.NewEncoder(w).Encode("ok")
}
