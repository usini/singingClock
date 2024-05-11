#ifndef SCREEN_H
#define SCREEN_H

#include "pinout.h"
#include "ui.h"

// FileSystem / SD
#include <FS.h>
#include "LittleFS.h"

// Screen
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>

// Capacitve
#include <XPT2046_Bitbang.h>
#include "icons/wifi_icon.h"
#include "icons/light_off.h"
#include "icons/light_on.h"
#include "icons/sound_mute.h"
#include "icons/sound_play.h"
#include "icons/play.h"

class Screen
{
public:
    Screen();
    XPT2046_Bitbang ts = XPT2046_Bitbang(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS);
    bool setup();
    void status();
    bool draw_with_transparency = false;
    void redrawBackground();
    void drawButton(int pos, int icon);
    void redrawClock(String timeString, String dateString);
    void blinkingWiFi();
    void redrawWiFiIcon();

private:
    bool wifiBlink;
    TFT_eSPI tft;
    // TFT ESPI Sprite
    TFT_eSprite txtSprite = TFT_eSprite(&tft);
    TFT_eSprite txt2Sprite = TFT_eSprite(&tft);
    static Screen *instance;
    static bool tftOutputStatic(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap);
    bool tftOutput(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap);
    
};

#endif // SCREEN_H