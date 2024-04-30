// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include "peripherals.h"
#include "ui.h"
//#include "timer.h"
#include "timer_rtc.h"
#include "usbcommands.h"
bool redrawInProgress = false;
bool screen_pressed = false;

void setup()
{
  Serial.begin(115200);
  peripheralsInit();
  serialInit();
  uiInit();
  redrawBackground();
  rtc_start();
}

void loop()
{
  rtc_loop();
  //redrawBackgroundNeeded = true;
  serialLoop();
  delay(1000);
  /*
  if (minuteTick() || redrawClockNeeded)
  {
    redrawInProgress = true;
    redrawBackground();
    redraw_clock();

    for (int i = 0; i < 3; i++)
    {
      buttonRedrawNeeded[i] = true;
    }

    Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
    redrawInProgress = false;
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
  */
}
