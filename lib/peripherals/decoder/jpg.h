bool draw_with_transparency = false;

bool jpgDraw(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    if(draw_with_transparency){
        tft.pushImage(x, y, w, h, bitmap, TFT_BLACK);
    } else {
        tft.pushImage(x, y, w, h, bitmap);
    }
    return 1;
}