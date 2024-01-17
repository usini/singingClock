
#include "pinout.h"
#include <WiFi.h>
#include <FS.h>
#include "LittleFS.h"
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <Preferences.h>
#include <ezTime.h>

TFT_eSPI tft = TFT_eSPI();
SPIClass spi_sd = SPIClass(VSPI);

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    tft.pushImage(x, y, w, h, bitmap);
    return 1;
}

bool screen_init()
{
    Serial.println("[🖥️  Display] 👋 Init");
    tft.init();
    tft.setRotation(1);
    tft.setSwapBytes(true);
    TJpgDec.setJpgScale(1);
    TJpgDec.setCallback(tft_output);
    return true;
}

bool fs_init()
{
    Serial.println("[💾 FS] 👋 Init");
    bool status = LittleFS.begin(false, "/flash");
    if (status)
    {
        Serial.println("[💾 FS] 🟢 OK");
    }
    else
    {
        Serial.println("[💾 FS] 🔴 Failed");
    }
    return status;
}

bool sd_init()
{
    Serial.println("[💾 SD] Init");
    spi_sd.begin(SD_SCK, SD_MISO /* MISO */, SD_MOSI /* MOSI */, SD_CS /* SS */);
    bool status = SD.begin(SD_CS /* SS */, spi_sd, 80000000, "/sdcard");
    if (status)
    {
        Serial.println("[💾 SD] 🟢 OK");
    }
    else
    {
        Serial.println("[💾 SD] 🔴 Failed");
    }
    return status;
}

bool peripherals_init()
{
    bool fs_status = fs_init();
    bool sd_status = sd_init();
    bool video_status = screen_init();
    // bool audio_status = audio_init();
    if (video_status && sd_status && fs_init)
    {
        return true;
    }
    else
    {
        return false;
    }
    /*
    if (sd_status)
    {
        drawJPGpos(288, 0, "/sdcard.jpg");
    }
    else
    {
        drawJPGpos(288, 0, "/nosdcard.jpg");
    }

    else
    {
        return false;
    }
    */
}
