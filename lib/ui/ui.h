TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite txtSprite = TFT_eSprite(&tft);

bool wifi_blink = false;
bool redraw_background_needed = false;
bool redraw_wifi_icon_needed = false;

const int BUTTON_1_X = 12;
const int BUTTON_2_X = 126;
const int BUTTON_3_X = 236;
const int BUTTON_Y = 160;
const int BUTTON_SIZE = 70;

void redraw_background()
{
    if (redraw_background_needed)
    {
        TJpgDec.drawFsJpg(0, 0, "/bg.jpg", LittleFS);
        redraw_background_needed = false;
    }
}

void draw_button(int pos, String filename){
    int position = 0;
    switch(pos){
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
    TJpgDec.setCallback(tft_output);
    draw_with_transparency = true;
    TJpgDec.drawFsJpg(position,BUTTON_Y, filename, LittleFS);
    draw_with_transparency = false;
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
