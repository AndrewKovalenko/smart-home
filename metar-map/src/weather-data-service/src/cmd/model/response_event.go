package model

import standalone_service_models "weatherdataservice/cmd/standalone_service/models"

// NOTE: response event format
// {
// 	"statusCode": 201,
// 	 "headers": {
// 			 "Content-Type": "application/json",
// 			 "My-Custom-Header": "Custom Value"
// 	 },
// 	 "body": "{ \"message\": \"Hello, world!\" }",
// 	 "cookies": [
// 			 "Cookie_1=Value1; Expires=21 Oct 2021 07:48 GMT",
// 			 "Cookie_2=Value2; Max-Age=78000"
// 	 ],
// 	 "isBase64Encoded": false
// }

type AWSResponseFormat struct {
	Body standalone_service_models.GetFlightCategoryResponse `json:"body"` //standalone_models.GetFlightCategoryResponse
}
