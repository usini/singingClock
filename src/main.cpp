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
    redrawInProgress = true;
    redrawBackground();
    redraw_clock();

    for (int i = 0; i < 3; i++)
    {
      buttonRedrawNeeded[i] = true;
    }

    if (connected)
    {
      redraw_wifi_icon();
    }
    Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
    redrawInProgress = false;
  }
  if (!connected)
  {
    if (secondTick())
    {
      redrawInProgress = true;
      blinking_wifi();
      redrawInProgress = false;
    }
  }

  if (buttonRedrawNeeded[0])
  {
    redrawInProgress = true;
    if (buttonState[0])
    {
      drawButton(0, LIGHT_ON);
    }
    else
    {
      drawButton(0, LIGHT_OFF);
    }
    buttonRedrawNeeded[0] = false;
    redrawInProgress = false;
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
        if (buttonState[0])
        {
          if (mqttConnected)
          {
            mqttClient.publish("lampe/salon/command", 1, false, "off");
          }
        }
        else
        {
          if (mqttConnected)
          {
            mqttClient.publish("lampe/salon/command", 1, false, "on");
          }
        }
        buttonState[0] = !buttonState[0];
      }
      if (p.x >= 120 && p.x <= 190)
      {
        Serial.println("Button 1 Pressed");
        if (buttonState[1])
        {

        }
        else
        {

        }
        buttonState[1] = !buttonState[1];
      }
      if (p.x >= 220)
      {
        Serial.println("Button 1 Pressed");
        if (buttonState[2])
        {

        }
        else
        {

        }
        buttonState[2] = !buttonState[2];
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
