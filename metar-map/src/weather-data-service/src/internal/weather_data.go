package internal

type WeatherStationData struct {
	Properties map[string]any `json:"properties"`
}

type AviationWeatherAPIResponse struct {
	StationsData []WeatherStationData `json:"features"`
}
