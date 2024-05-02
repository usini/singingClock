// TFT ESPI Sprite
TFT_eSprite txtSprite = TFT_eSprite(&tft);
TFT_eSprite txt2Sprite = TFT_eSprite(&tft);

const int WIFI_ICON = 0;
const int LIGHT_OFF = 1;
const int LIGHT_ON = 2;

#include "icons/wifi_icon.h"
#include "icons/light_off.h"
#include "icons/light_on.h"

// TFT Redraw
bool wifiBlink = false;
bool redrawBackgroundNeeded = true;
bool redrawWifiIconNeeded = false;
bool redrawClockNeeded = true;

// TFT Buttons
const int BUTTON_1_X = 12;
const int BUTTON_2_X = 126;
const int BUTTON_3_X = 236;
const int BUTTON_Y = 160;
const int BUTTON_SIZE = 70;

void redrawBackground()
{
    if (redrawBackgroundNeeded)
    {
        TJpgDec.drawFsJpg(0, 0, "/bg.jpg", LittleFS);
        redrawBackgroundNeeded = false;
    }
}

void drawButton(int pos, int icon)
{
    int position = 0;
    switch (pos)
    {
    case 0:
        position = BUTTON_1_X;
        break;
    case 1:
        position = BUTTON_2_X;
        break;
    case 2:
        position = BUTTON_3_X;
        break;
    }

    switch (icon)
    {
    case WIFI_ICON:
        tft.pushImage(position, BUTTON_Y, BUTTON_SIZE, BUTTON_SIZE, wifi_icon, TFT_BLACK);
        break;
    case LIGHT_OFF:
        tft.pushImage(position, BUTTON_Y, BUTTON_SIZE, BUTTON_SIZE, light_off, TFT_BLACK);
        break;
    case LIGHT_ON:
        tft.pushImage(position, BUTTON_Y, BUTTON_SIZE, BUTTON_SIZE, light_on, TFT_BLACK);
        break;
    }
}

void redrawClock()
{
    txtSprite.loadFont("/Calibri-96", LittleFS);
    txtSprite.setCursor(0, 0);
    txtSprite.fillScreen(TFT_BLACK);
    //String time = myTz.dateTime("H:i");
    txtSprite.print(timeToString(false));
    txtSprite.pushSprite(55, 52, TFT_BLACK);

    txt2Sprite.loadFont("/Calibri-24", LittleFS);
    txt2Sprite.setCursor(0, 0);
    txt2Sprite.fillScreen(TFT_BLACK);
    String date = dateToString();
    txt2Sprite.print(date);
    txt2Sprite.pushSprite(100, 125, TFT_BLACK);

    if (redrawClockNeeded)
    {
        redrawClockNeeded = false;
    }
}

void blinking_wifi()
{
    if (!wifiBlink)
    {
        tft.pushImage(0, 0, 16, 16, wifi_icon, TFT_BLACK);
    }
    else
    {
        tft.fillRect(0, 0, 16, 16, 0x39E7);
    }
    wifiBlink = !wifiBlink;
}

void redraw_wifi_icon()
{
    tft.pushImage(0, 0, 16, 16, wifi_icon, TFT_BLACK);
}

void uiInit()
{
    txtSprite.createSprite(240, 96);
    txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
    txtSprite.setSwapBytes(true);
    txt2Sprite.createSprite(240, 96);
    txt2Sprite.setTextColor(TFT_WHITE, TFT_BLACK);
    txt2Sprite.setSwapBytes(true);
}