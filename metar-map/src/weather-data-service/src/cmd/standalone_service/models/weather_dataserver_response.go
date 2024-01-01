package models

type Metar struct {
	StationId   string
	Visibility  float32
	CloudLayers []uint
}
