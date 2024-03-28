#include <Arduino.h>
#include <Adafruit_LEDBackpack.h>
#include <ezButton.h>

Adafruit_24bargraph bar = Adafruit_24bargraph();
int led_number = 0;
ezButton toggle_button(7);
bool run_bargraph = false;
uint64_t cycles = 0;

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

  if (run_bargraph && (cycles % 100 == 0))
  {
    bar.setBar(led_number, LED_GREEN);
    led_number++;

    Serial.println("Setting LED # " + led_number);

    bar.writeDisplay();

    if (led_number > 23)
    {
      led_number = 0;
      bar.clear();
    }
  }

  delay(10);

  if (cycles > 18446744073709551000)
  {
    cycles = 0;
  }
  else
  {
    cycles++;
  }
}