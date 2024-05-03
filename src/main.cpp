// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include "pinout.h"

#include "Peripherals/Peripherals.h"
TFT_eSPI tft = TFT_eSPI();
Peripherals peripherals = Peripherals();

#include "timer_conversion.h"
#include "timer_rtc.h"

#include "ui.h"
#include "Audio/Audio.h"
#include "usbcommands.h"

bool screen_pressed = false;

Audio audio = Audio();


void setup()
{
  peripherals.setup();
  serialInit();
  uiInit();
  audio.setup(I2S_SCLK,I2S_LRCK,I2S_DOUT);
  rtcStart();
  audio.playStartup();
}

void loop()
{
  audio.loop();
  serialLoop();

  if (minuteTick())
  {
    String path = "/time/" + timeToString(true);
    String audioFileToPlay = path + "/" + peripherals.pickRandomFile(path);
    Serial.println(audioFileToPlay);
    redrawBackground();
    redrawClock();
    Serial.println("[⏲️TIME] - " + timeToString(false));
    if (SD.exists(audioFileToPlay))
    {
      audio.playFile(audioFileToPlay);
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
