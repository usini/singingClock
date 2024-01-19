// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include "peripherals.h"
#include "internet.h"
#include "timer.h"
#include "clock.h"
#include "ui.h"
#include "usbcommands.h"

void setup()
{
  Serial.begin(115200);
  peripherals_init();
  wifi_start();
  serial_init();
  clock_init();
}

void loop()
{
  currentMillis = millis();
  redraw_background_needed = true;
  serial_loop();

  if (minute_tick() || redraw_clock_needed)
  {
    redraw_background();
    redraw_clock();
    Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
    if (connected)
    {
      redraw_wifi_icon();
    }
  }
  if (!connected)
  {
    if (second_tick())
    {
      blinking_wifi();
    }
  }
}
