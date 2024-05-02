// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include "peripherals.h"

#include "timer_conversion.h"
#include "timer_rtc.h"

#include "ui.h"
#include "audio.h"
#include "usbcommands.h"

bool redrawInProgress = false;
bool screen_pressed = false;

void setup()
{
  Serial.begin(115200);
  peripheralsInit();
  serialInit();
  uiInit();
  audioInit();
  rtcStart();
  playStartup();
}

void loop()
{
  mp3Loop();
  serialLoop();

  if (minuteTick())
  {
    String path = "/time/" + timeToString(true);
    String audioFileToPlay = path + "/" + PickRandomFile(path);
    Serial.println(audioFileToPlay);

    redrawBackgroundNeeded = true;
    redrawInProgress = true;
    redrawBackground();
    redrawClock();
    Serial.println("[⏲️TIME] - " + timeToString(false));
    redrawInProgress = false;
    if (SD.exists(audioFileToPlay))
    {
      playFile(audioFileToPlay);
    }
    else
    {
      Serial.println("No file for this time...");
    }
  }

  /*
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
