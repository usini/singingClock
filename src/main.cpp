// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include "peripherals.h"
#include "internet.h"
#include "ui.h"
#include "timer.h"
#include "usbcommands.h"

bool screen_pressed = false;

void setup()
{
  Serial.begin(115200);
  peripheralsInit();
  wifiStart();
  serialInit();
  uiInit();
}

void loop()
{
  redrawBackgroundNeeded = true;
  serialLoop();

  if (minuteTick() || redrawClockNeeded)
  {
    redraw_in_progress = true;
    redrawBackground();
    redraw_clock();

    for (int i = 0; i < 3; i++)
    {
      button_redraw_needed[i] = true;
    }

    if (connected)
    {
      redraw_wifi_icon();
    }
    Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
    redraw_in_progress = false;
  }
  if (!connected)
  {
    if (secondTick())
    {
      redraw_in_progress = true;
      blinking_wifi();
      redraw_in_progress = false;
    }
  }

  if (button_redraw_needed[0])
  {
    redraw_in_progress = true;
    if (button_state[0])
    {
      drawButton(0, LIGHT_ON);
    }
    else
    {
      drawButton(0, LIGHT_OFF);
    }
    button_redraw_needed[0] = false;
    redraw_in_progress = false;
  }

  TouchPoint p = ts.getTouch();

  if (p.zRaw > 200 && !screen_pressed)
  {
    screen_pressed = true;
    if (p.y >= 160)
    {
      if (p.x >= 30 && p.x <= 100)
      {
        Serial.println("Button 1 Pressed");
        if (button_state[0])
        {
          if (mqtt_connected)
          {
            mqttClient.publish("lampe/salon/command", 1, false, "off");
          }
        }
        else
        {
          if (mqtt_connected)
          {
            mqttClient.publish("lampe/salon/command", 1, false, "on");
          }
        }
        button_state[0] = !button_state[0];
      }
      if (p.x >= 120 && p.x <= 190)
      {
        Serial.println("Button 1 Pressed");
        if (button_state[1])
        {

        }
        else
        {

        }
        button_state[1] = !button_state[1];
      }
      if (p.x >= 220)
      {
        Serial.println("Button 1 Pressed");
        if (button_state[2])
        {

        }
        else
        {

        }
        button_state[2] = !button_state[2];
      }
    }

    Serial.print("[🖥️👉 Display] Touch: ");
    Serial.print(p.x);
    Serial.print(",");
    Serial.println(p.y);
    delay(100);
  }
  if (p.zRaw <= 200 && screen_pressed)
  {
    screen_pressed = false;
  }
}
