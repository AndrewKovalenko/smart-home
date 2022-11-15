package main

import (
	"context"
	"encoding/json"
	"errors"
	"weatherdataservice/internal"
	"weatherdataservice/internal/models"

	"github.com/aws/aws-lambda-go/lambda"
)

func HandleRequest(ctx context.Context, request models.GetFlightCategoryRequest) (string, error) {
	stationFlightCategories, err := internal.GetWeather(request.Stations)

	if err != nil {
		return "", errors.New("unable to get weather")
	}

	response, err := json.Marshal(stationFlightCategories)

	if err != nil {
		return "", errors.New("error serializing data")
	}

	return string(response), nil
}

func main() {
	lambda.Start(HandleRequest)
}
