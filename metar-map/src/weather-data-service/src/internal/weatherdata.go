package internal

type WeatherStationData struct {
	Properties map[string]string `json:"properties"`
}

type AviationWeatherAPIResponse struct {
	StationsData []WeatherStationData `json:"features"`
}
