package models

import "encoding/json"

type CloudLayer struct {
	Type         string `json:"cover"`
	BaseAltitude uint   `json:"base"`
}

type WeatherDataServerResponse struct {
	StationId  string          `json:"icaoId"`
	Visibility json.RawMessage `json:"visib"`
	Clouds     []CloudLayer    `json:"clouds"`
}
