// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include "peripherals.h"
#include "internet.h"
#include "timer.h"
#include "ui.h"
#include "clock.h"
#include "usbcommands.h"

/*
void drawButton()
{
  tft.fillSmoothRoundRect(12, 160, 70, 70, 5, TFT_WHITE, TFT_WHITE);
  tft.fillSmoothRoundRect(126, 160, 70, 70, 5, TFT_WHITE, TFT_WHITE);
  tft.fillSmoothRoundRect(236, 160, 70, 70, 5, TFT_WHITE, TFT_WHITE);
}
*/

bool button_state[3] = {false,false,false};
bool screen_pressed = false;
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
    draw_button(0, "/light_off.jpg");
    draw_button(1, "/light_off.jpg");
    draw_button(2, "/light_off.jpg");
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

  TouchPoint p = ts.getTouch();

  if (p.zRaw > 200 && !screen_pressed)
  {
    screen_pressed = true;
    if (p.y >= 160)
    {
      if (p.x >= 31 && p.x <= 96)
      {
        Serial.println("Button 1 Pressed");
        if(button_state[0]){
          draw_button(0, "/light_off.jpg");
        } else {
          draw_button(0, "/light_on.jpg");
        }
        button_state[0] = !button_state[0];
      }
      if (p.x >= 120 && p.x <= 190)
      {
                Serial.println("Button 1 Pressed");
        if(button_state[1]){
          draw_button(1, "/light_off.jpg");
        } else {
          draw_button(1, "/light_on.jpg");
        }
        button_state[1] = !button_state[1];
      }
      if (p.x >= 220)
      {
               Serial.println("Button 1 Pressed");
        if(button_state[2]){
          draw_button(2, "/light_off.jpg");
        } else {
          draw_button(2, "/light_on.jpg");
        }
        button_state[2] = !button_state[2];
      }
    }

    Serial.print(p.x);
    Serial.print(",");
    Serial.println(p.y);
    delay(100);
  }
  if(p.zRaw <= 200 && screen_pressed){
    screen_pressed = false;
  }
}
