default: dist

standalone:
	GOOS=linux GOARCH=arm GOARM=5 go build -o build/standalone/flightCategoryService ./cmd/standalone_service/main.go

lambda:
	GOARCH=amd64 GOOS=linux CGO_ENABLED=0 go build -o ./build/lambda/getFlightCategory ./cmd/lambda/main.go &&\
	cp ./cmd/standalone_service/weather-data-config.yaml ./build/lambda &&\
	zip -9jpr ./build/lambda/getFlightCategory.zip ./build/lambda/*

clean:
	rm -rf ./build/*