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

// TFT Time
const int TIME_X = 55;
const int TIME_Y = 52;
const int DATE_X = 90;
const int DATE_Y = 125:

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
    // Show Time
    txtSprite.loadFont("/Calibri-96", LittleFS);
    txtSprite.setCursor(0, 0);
    txtSprite.fillScreen(TFT_BLACK);
    txtSprite.print(timeToString(false));
    txtSprite.pushSprite(TIME_X, TIME_Y, TFT_BLACK);

    // Show Date
    txt2Sprite.loadFont("/Calibri-24", LittleFS);
    txt2Sprite.setCursor(0, 0);
    txt2Sprite.fillScreen(TFT_BLACK);
    txt2Sprite.print(dateToString());
    txt2Sprite.pushSprite(DATE_X, DATE_Y, TFT_BLACK);

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