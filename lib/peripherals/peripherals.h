
// Pinout
#include "pinout.h"

// FileSystem / SD
#include <FS.h>
#include "LittleFS.h"

// Screen
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>

#include <XPT2046_Bitbang.h>

// Spi Device (we are forced to bitbang XPT2046 because we have 3 SPI Device and 2 SPI Bus)
// Could probably make up for it with CS...
TFT_eSPI tft = TFT_eSPI();
//#include "decoder/png.h"
#include "decoder/jpg.h"
SPIClass spi_sd = SPIClass(VSPI);
XPT2046_Bitbang ts = XPT2046_Bitbang(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS);

// Status for peripherals
bool fsStatus = false;
bool sdStatus = false;
bool audioStatus = false;
bool videoStatus = false;

void getMemory()
{
    char temp[300];
    sprintf(temp, "Heap: Free:%i, Min:%i, Size:%i, Alloc:%i", ESP.getFreeHeap(), ESP.getMinFreeHeap(), ESP.getHeapSize(), ESP.getMaxAllocHeap());
    Serial.println(temp);
}

bool screenInit()
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

bool fsInit()
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

bool sdInit()
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

void peripheralsStatus()
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

bool peripheralsInit()
{
    randomSeed(analogRead(34));
    fsStatus = fsInit();
    sdStatus = sdInit();
    videoStatus = screenInit();
    // bool audioStatus = audio_init();
    if (videoStatus && sdStatus && fsInit)
    {
        return true;
    }
    else
    {
        return false;
    }
}

String PickRandomFile(String folder){
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
