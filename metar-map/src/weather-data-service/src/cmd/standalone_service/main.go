package main

import (
	"log"
	"net/http"

	httphandlers "weatherdataservice/cmd/standalone_service/http_handlers"

	"github.com/gorilla/mux"
)

func main() {
	router := mux.NewRouter().StrictSlash(true)
	router.HandleFunc("/health", httphandlers.HealthCheck)
	router.HandleFunc("/getFlightCategory/{stations}", httphandlers.GetStationsFlightCategory).Methods("GET")
	log.Fatal(http.ListenAndServe(":8000", router))
}
