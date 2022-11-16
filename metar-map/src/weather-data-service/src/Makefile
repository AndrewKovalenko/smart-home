default: dist

standalone:
	GOOS=linux GOARCH=arm GOARM=5 go build -o build/standalone/flightCategoryService ./cmd/standalone_service/main.go

lambda:
	GOOS=linux CGO_ENABLED=0 go build -o ./build/lambda/getFlightCategory ./cmd/lambda/main.go &&\
	zip -9jpr ./build/lambda/getFlightCategory.zip ./build/lambda/getFlightCategory

clean:
	rm -rf ./build/*