package main

import (
	"context"
	"errors"
	"fmt"
	"log"
	"strings"
	lambda_models "weatherdataservice/cmd/model"
	"weatherdataservice/internal"

	"github.com/aws/aws-lambda-go/lambda"
)

func HandleRequest(ctx context.Context, request lambda_models.AWSRequestEvent) (lambda_models.AWSResponseFormat, error) {
	log.Println(fmt.Sprintf("Stations: %s", request.QueryStringParameters.Stations))
	stationsCollection := strings.Split(request.QueryStringParameters.Stations, ",")
	stationFlightCategories, err := internal.GetWeather(stationsCollection)

	if err != nil {
		return lambda_models.AWSResponseFormat{}, errors.New("unable to get weather")
	}

	return lambda_models.AWSResponseFormat{Body: stationFlightCategories}, nil
}

func main() {
	lambda.Start(HandleRequest)
}
