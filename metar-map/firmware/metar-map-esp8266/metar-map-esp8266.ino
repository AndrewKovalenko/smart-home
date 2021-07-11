#include "metar-map-controller/controller.h"

unsigned int state = LOW; // Variable for the state of the LED
void setup()
{
  Serial.begin(115200);         // Set the communication speed
  pinMode(LED_BUILTIN, OUTPUT); // Set the GPIO pin as an output
}
void loop()
{
  digitalWrite(LED_BUILTIN, state);  // Set the LED state
  Serial.print("LED state: ");       // Print "LED state: "
  Serial.println(state);             // Print the state variable
                                     // plus a carriage return
  state = state == LOW ? HIGH : LOW; // Change state LOW <-> HIGH
  delay(1000);                       // Wait for a second
}
