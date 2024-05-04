// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include "pinout.h"

#include "Filesystem/Filesystem.h"
#include "Screen/Screen.h"

#include "timer_conversion.h"
#include "timer_rtc.h"

#include "Audio/Audio.h"
#include "usbcommands.h"

bool screen_pressed = false;

Audio audio = Audio();
Filesystem filesystem = Filesystem();
Screen screen = Screen();

bool buttonState[3] = {false, false, false};

void redrawButtons()
{
  if (buttonState[0])
  {
    screen.drawButton(0, SOUND_MUTE);
  }
  else
  {
    screen.drawButton(0, SOUND_PLAY);
  }
  screen.drawButton(2, PLAY);
}

void setup()
{
  serialInit();
  filesystem.setup();
  screen.setup();
  audio.setup(I2S_SCLK, I2S_LRCK, I2S_DOUT);
  rtcStart();
  audio.playStartup();
}

void loop()
{
  audio.loop();
  serialLoop();

  if (minuteTick())
  {
    screen.redrawBackground();
    screen.redrawClock(timeToString(false), dateToString());
    redrawButtons();
    Serial.println("[⏲️TIME] - " + timeToString(false));
    Serial.println("[🗓️ DAY] - " + String(dayWeek()));

    String path = "/time/" + timeToString(true);
    String audioFileToPlay = path + "/" + filesystem.pickRandomFile(path);
    Serial.println(audioFileToPlay);
    if (SD.exists(audioFileToPlay))
    {
      audio.playFile(audioFileToPlay);
    }
    else
    {
      Serial.println("No file for this time...");
    }
  }

  TouchPoint p = screen.ts.getTouch();

  if (p.zRaw > 200 && !screen_pressed)
  {
    //@todo Not optimized should redraw just the button
    screen_pressed = true;
    Serial.print("[🖥️ 👉 Display] Touch: ");
    Serial.print(p.x);
    Serial.print(",");
    Serial.println(p.y);
    delay(100);
    if (p.y >= 160)
    {
      Serial.println("Button Pressed");
      if (p.x >= 30 && p.x <= 100)
      {

        if (buttonState[0])
        {
          Serial.println("UnMute");
          audio.unmute();
        }
        else
        {
          Serial.println("Mute");
          audio.mute();
        }
        buttonState[0] = !buttonState[0];
      }
      else if (p.x >= 220)
      {
        Serial.println("Button Pressed : Play");
        String path = "/time/" + timeToStringHourOnly();
        String audioFileToPlay = path + "/" + filesystem.pickRandomFile(path);
        Serial.println(audioFileToPlay);
        if (SD.exists(audioFileToPlay))
        {
          audio.playFile(audioFileToPlay);
        }
        else
        {
          Serial.println("No file for this time...");
        }
      }
      screen.redrawBackground();
      screen.redrawClock(timeToString(false), dateToString());
      redrawButtons();
    }
  }

  if (p.zRaw <= 200 && screen_pressed)
  {
    Serial.println("Unpressed");
    screen_pressed = false;
  }
}
