package models

type Metar struct {
	StationId   string
	Visibility  int
	CloudLayers []uint
}
