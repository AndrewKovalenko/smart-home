package repositories

import (
	"errors"
	"log"
	"os"
	"weatherdataservice/internal/entities"

	"gopkg.in/yaml.v3"
)

const configPath = "./weather-data-config.yaml"

func readConfig() *entities.ServiceConfig {
	configFile, err := os.ReadFile(configPath)
	result := entities.ServiceConfig{}

	if err != nil {
		log.Println("corrupted or missing config file")
		return nil
	}

	err = yaml.Unmarshal(configFile, &result)

	if err != nil {
		log.Println("unable to parse config file")
		return nil
	}

	return &result
}

var serviceConfig *entities.ServiceConfig = readConfig()

func GetServiceConfig() (entities.ServiceConfig, error) {
	if serviceConfig == nil {
		return entities.ServiceConfig{}, errors.New("no service config")
	}

	return *serviceConfig, nil
}
