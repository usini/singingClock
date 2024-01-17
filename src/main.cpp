// Animates white pixels to simulate flying through a star field
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <FS.h>
#include "LittleFS.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite txtSprite = TFT_eSprite(&tft);
int x = 0;

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void setup()
{
  Serial.begin(115200);
  LittleFS.begin();
  tft.init();

  tft.setRotation(1);
  tft.setSwapBytes(true);
  TJpgDec.setJpgScale(1);
  TJpgDec.setCallback(tft_output);
  /*
  background.setColorDepth(8);
  if (background.createSprite(320, 240) == nullptr)
    Serial.println("Sprite not created");
  else
    Serial.println("Sprite OK");
  background.setSwapBytes(true);
  */
  //TJpgDec.drawFsJpg(0, 0, "/bg.jpg", LittleFS);
  txtSprite.createSprite(240, 96);
  txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
  txtSprite.setSwapBytes(true);
  txtSprite.loadFont("/Calibri-96", LittleFS);
}

void loop()
{
  TJpgDec.drawFsJpg(0, 0, "/bg.jpg", LittleFS);
  txtSprite.setCursor(0,0);
  txtSprite.print(String("12:12"));
  txtSprite.pushSprite(55,52, TFT_BLACK);
  //background.pushSprite(0, 0);
  Serial.println("draw" + String(x));
  x++;
  delay(1000);
}
