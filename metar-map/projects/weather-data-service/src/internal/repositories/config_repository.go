package repositories

import (
	"errors"
	"log"
	"os"
	"path"
	"path/filepath"
	"weatherdataservice/internal/entities"

	"gopkg.in/yaml.v3"
)

const configFileName = "weather-data-config.yaml"

var executableDirectory, directoryReadingError = filepath.Abs(filepath.Dir(os.Args[0]))

func readConfig() *entities.ServiceConfig {
	if directoryReadingError != nil {
		log.Println("error reading config path")
		return nil
	}

	configFilePath := path.Join(executableDirectory, configFileName)
	configFile, err := os.ReadFile(configFilePath)
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
