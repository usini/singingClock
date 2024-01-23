// TFT Png
File pngfile;
PNG png;
int png_x = 0;
int png_y = 0;

void pngDraw(PNGDRAW *pDraw)
{
    uint16_t lineBuffer[70];        // Line buffer for rendering
    uint8_t maskBuffer[1 + 70 / 8]; // Mask buffer

    png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_LITTLE_ENDIAN, 0xffffffff);

    if (png.getAlphaMask(pDraw, maskBuffer, 255))
    {
        // Note: pushMaskedImage is for pushing to the TFT and will not work pushing into a sprite
        tft.pushMaskedImage(png_x, png_y + pDraw->y, pDraw->iWidth, 1, lineBuffer, maskBuffer);
    }
}

void *pngOpen(const char *filename, int32_t *size)
{
    pngfile = LittleFS.open(filename, "r");
    *size = pngfile.size();
    return &pngfile;
}

void pngClose(void *handle)
{
    Serial.println("Closed");
    File pngfile = *((File *)handle);
    if (pngfile)
        pngfile.close();
    png.setBuffer(0);
}

int32_t pngRead(PNGFILE *page, uint8_t *buffer, int32_t length)
{
    if (!pngfile)
        return 0;
    page = page; // Avoid warning
    return pngfile.read(buffer, length);
}

int32_t pngSeek(PNGFILE *page, int32_t position)
{
    if (!pngfile)
        return 0;
    page = page; // Avoid warning
    return pngfile.seek(position);
}
