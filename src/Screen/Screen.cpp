#include "Screen.h"
#include "pinout.h"

Screen* Screen::instance = nullptr; //!< Initialisation du pointeur statique vers l'instance de la classe Display.

Screen::Screen() {
    instance = this;
}

bool Screen::tftOutputStatic(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap) {
    if (instance) {
        return instance->tftOutput(x, y, w, h, bitmap);
    }
    return false;
}

bool Screen::tftOutput(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    if(draw_with_transparency){
        tft.pushImage(x, y, w, h, bitmap, TFT_BLACK);
    } else {
        tft.pushImage(x, y, w, h, bitmap);
    }
    return 1;
}

bool Screen::setup()
{
    instance = this;
    Serial.println("[🖥️  Display] 👋 Init");
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
    tft.setSwapBytes(true);
    TJpgDec.setJpgScale(1);
    TJpgDec.setCallback(&Screen::tftOutputStatic);
    ts.begin();

    txtSprite.createSprite(240, 96);
    txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
    txtSprite.setSwapBytes(true);
    txt2Sprite.createSprite(240, 96);
    txt2Sprite.setTextColor(TFT_WHITE, TFT_BLACK);
    txt2Sprite.setSwapBytes(true);
    return true;
}

void Screen::redrawBackground()
{
    TJpgDec.drawFsJpg(0, 0, "/bg.jpg", LittleFS);
}

void Screen::drawButton(int pos, int icon)
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
    case SOUND_MUTE:
        tft.pushImage(position, BUTTON_Y, BUTTON_SIZE, BUTTON_SIZE, sound_mute, TFT_BLACK);
        break;
    case SOUND_PLAY:
        tft.pushImage(position, BUTTON_Y, BUTTON_SIZE, BUTTON_SIZE, sound_play, TFT_BLACK);
        break;
    case PLAY:
        tft.pushImage(position, BUTTON_Y, BUTTON_SIZE, BUTTON_SIZE, play, TFT_BLACK);
        break;
    }
}

void Screen::redrawClock(String timeString, String dateString)
{
    // Show Time
    txtSprite.loadFont("/Calibri-96", LittleFS);
    txtSprite.setCursor(0, 0);
    txtSprite.fillScreen(TFT_BLACK);
    txtSprite.print(timeString);
    txtSprite.pushSprite(TIME_X, TIME_Y, TFT_BLACK);

    // Show Date
    txt2Sprite.loadFont("/Calibri-24", LittleFS);
    txt2Sprite.setCursor(0, 0);
    txt2Sprite.fillScreen(TFT_BLACK);
    txt2Sprite.print(dateString);
    txt2Sprite.pushSprite(DATE_X, DATE_Y, TFT_BLACK);
}

void Screen::blinkingWiFi()
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

void Screen::redrawWiFiIcon()
{
    tft.pushImage(0, 0, 16, 16, wifi_icon, TFT_BLACK);
}
