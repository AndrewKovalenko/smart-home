package repositories

import (
	"errors"
	"io"
	"net/http"
)

const boxDataUrl = "https://aviationweather.gov/cgi-bin/json/MetarJSON.php?zoom=7&filter=prior&density=all&taf=0&bbox=-124.57,46.56,-120.14,48.8"

func GetWeatherData() ([]byte, error) {
	response, err := http.Get(boxDataUrl)

	if err != nil {
		return nil, errors.New("unable to recive weaterh data from aw api")
	}

	defer response.Body.Close()

	body, err := io.ReadAll(response.Body)

	if err != nil {
		return nil, errors.New("unabel to read aw data response")
	}

	return body, nil
}
