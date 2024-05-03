#include "Peripherals.h"
#include "pinout.h"

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

void Peripherals::getMemory()
{
    char temp[300];
    sprintf(temp, "Heap: Free:%i, Min:%i, Size:%i, Alloc:%i", ESP.getFreeHeap(), ESP.getMinFreeHeap(), ESP.getHeapSize(), ESP.getMaxAllocHeap());
    Serial.println(temp);
}

bool Peripherals::screenSetup()
{
    Serial.println("[🖥️  Display] 👋 Init");
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
    tft.setSwapBytes(true);
    TJpgDec.setJpgScale(1);
    TJpgDec.setCallback(jpgDraw);
    ts.begin();
    return true;
}

bool Peripherals::fsSetup()
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

bool Peripherals::SDSetup()
{
    Serial.println("[💾 SD] 👋 Init");
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

void Peripherals::status()
{
    if (fsStatus)
    {
        Serial.println("[💾 FS] 🟢 OK");
    }
    else
    {
        Serial.println("[💾 FS] 🔴 Failed");
    }
    if (sdStatus)
    {
        Serial.println("[💾 SD] 🟢 OK");
    }
    else
    {
        Serial.println("[💾 SD] 🔴 Failed");
    }
    if (videoStatus)
    {
        Serial.println("[🖥️  Display] 🟢 OK");
    }
    else
    {
        Serial.println("[🖥️  Display] 🔴 Failed");
    }
}

bool Peripherals::setup()
{
    randomSeed(analogRead(34));
    fsStatus = fsSetup();
    sdStatus = SDSetup();
    videoStatus = screenSetup();
    if (videoStatus && sdStatus && fsStatus)
    {
        return true;
    }
    return false;
}



String Peripherals::pickRandomFile(String folder){
    File root = SD.open(folder);
    if(!root || !root.isDirectory()){
        Serial.println("Folder not exists");
        return "";
    }
    int fileCount = 0;
    File file = root.openNextFile();
    while(file){
        fileCount++;
        file = root.openNextFile();
    }
    Serial.println("Count file" + String(fileCount));
    int randomFileNumber = random(0,fileCount);
    Serial.println("Random is" + String(randomFileNumber));
    fileCount = 0;
    root = SD.open(folder);
    file = root.openNextFile();
    while(file){
        if(fileCount == randomFileNumber){
            Serial.println("filename:" + String(file.name()));
            return file.name();
        }
        file = root.openNextFile();
        fileCount++;
    }
    return "";
}
