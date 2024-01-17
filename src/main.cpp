// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include "peripherals.h"
#include "internet.h"
#include "clock.h"

void setup()
{
  Serial.begin(115200);
  peripherals_init();
  wifi_start();
  clock_init();
  // clock_start();
}

unsigned long previousMillisMinute = 0; // Pour l'action toutes les minutes
unsigned long previousMillisSecond = 0; // Pour l'action toutes les secondes
const long intervalMinute = 60000;      // 60 000 millisecondes = 1 minute
const long intervalSecond = 1000;       // 1 000 millisecondes = 1 seconde
bool wifi_blink = false;
bool redraw_background_needed = false;

void redraw_background()
{
  if (redraw_background_needed)
  {
    TJpgDec.drawFsJpg(0, 0, "/bg.jpg", LittleFS);
    redraw_background_needed = false;
  }
}

bool redraw_wifi_icon_needed = false;

void blinking_wifi()
{
}

void loop()
{

  unsigned long currentMillis = millis();
  redraw_background_needed = true;

  if (currentMillis - previousMillisMinute >= intervalMinute || redraw_clock_needed)
  {
    redraw_background();
    previousMillisMinute = currentMillis;
    txtSprite.setCursor(0, 0);
    txtSprite.fillScreen(TFT_BLACK);
    String time = myTz.dateTime("H:i");
    txtSprite.print(time);
    txtSprite.pushSprite(55, 52, TFT_BLACK);
    if (redraw_clock_needed)
    {
      redraw_clock_needed = false;
    }
    if(connected){
      tft.pushImage(0, 0, 16, 16, wifi_icon, TFT_BLACK);
    }
  }
  if (!connected)
  {
    if (currentMillis - previousMillisSecond >= intervalSecond)
    {
      previousMillisSecond = currentMillis;
      if (!wifi_blink)
      {
        Serial.println("ON");
        tft.pushImage(0, 0, 16, 16, wifi_icon, TFT_BLACK);
      }
      else
      {
        Serial.println("OFF");
        tft.fillRect(0,0,16,16,0x39E7);
      }
      //tft.pushSprite(0, 0, TFT_BLACK);
      wifi_blink = !wifi_blink;
    }
  }
}
