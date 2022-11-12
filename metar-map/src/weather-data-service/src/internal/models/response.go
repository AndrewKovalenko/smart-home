package models

type StationFlightCategory struct {
	StationId      string `json:"stationId"`
	FlightCategory string `json:"flightCategory"`
}

type GetFlightCategoryResponse []StationFlightCategory
