package entities

type ServiceConfig struct {
	StationOverrides map[string]string `yaml:"stationOverrides"`
}
