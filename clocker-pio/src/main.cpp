#include <Arduino.h>
#include <Adafruit_LEDBackpack.h>
#include <ezButton.h>

#define MAX_BRIGHTNESS 100
#define MIN_BRIGHTNESS 15

Adafruit_24bargraph bar = Adafruit_24bargraph();
int led_number = 0;
ezButton toggle_button(7);
bool run_bargraph = false;
unsigned long long cycles = 0;

uint8_t getBrightness(int sensor_read)
{
  if (sensor_read > 1000)
  {
    return MAX_BRIGHTNESS;
  }

  return uint8_t(sensor_read / (1000 / 15));
}

void setup()
{
  Serial.begin(9600);
  bar.begin(0x70);
  toggle_button.setDebounceTime(50);
}

void loop()
{
  toggle_button.loop();

  if (toggle_button.isPressed())
  {
    Serial.println("Pressed");
    run_bargraph = !run_bargraph;
    Serial.println(run_bargraph);
  }

  int light_strength = analogRead(A0);
  uint8_t bargraph_brightness = getBrightness(light_strength);

  if (cycles % 100 == 0)
  {
    Serial.println("Light value: " + String(light_strength));
    Serial.println("bargraph brightness: " + String(bargraph_brightness));

    if (run_bargraph)
    {
      bar.setBrightness(bargraph_brightness);
      bar.setBar(led_number, LED_GREEN);
      led_number++;

      Serial.println("Setting LED # " + String(led_number));

      bar.writeDisplay();

      if (led_number > 23)
      {
        led_number = 0;
        bar.clear();
      }
    }
  }

  delay(10);

  if (cycles > 18446744073709551000ULL)
  {
    cycles = 0;
  }
  else
  {
    cycles++;
  }
}