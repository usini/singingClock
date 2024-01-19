bool wifi_blink = false;
bool redraw_background_needed = false;
bool redraw_wifi_icon_needed = false;

void redraw_background()
{
    if (redraw_background_needed)
    {
        TJpgDec.drawFsJpg(0, 0, "/bg.jpg", LittleFS);
        redraw_background_needed = false;
    }
}

void redraw_clock()
{
    txtSprite.setCursor(0, 0);
    txtSprite.fillScreen(TFT_BLACK);
    String time = myTz.dateTime("H:i");
    txtSprite.print(time);
    txtSprite.pushSprite(55, 52, TFT_BLACK);
    if(redraw_clock_needed){
        redraw_clock_needed = false;
    }
}

void blinking_wifi()
{
    if (!wifi_blink)
    {
        tft.pushImage(0, 0, 16, 16, wifi_icon, TFT_BLACK);
    }
    else
    {
        tft.fillRect(0, 0, 16, 16, 0x39E7);
    }
    wifi_blink = !wifi_blink;
}

void redraw_wifi_icon()
{
    tft.pushImage(0, 0, 16, 16, wifi_icon, TFT_BLACK);
}
