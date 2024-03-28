#include <Arduino.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_24bargraph bar = Adafruit_24bargraph();
int led_number = 0;

void setup()
{
  bar.begin(0x70);
  pinMode(5, INPUT);
}

void loop()
{
  int buttonState = digitalRead(5);
  if (buttonState == LOW)
  {
    bar.setBar(led_number, LED_GREEN);
    led_number++;

    Serial.println("Setting LED # " + led_number);

    bar.writeDisplay();
    delay(1000);

    if (led_number > 23)
    {
      led_number = 0;
      bar.clear();
    }
  }
  else
  {
    Serial.println("Button ios not pressed!");
  }
}
