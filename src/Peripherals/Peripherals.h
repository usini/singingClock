#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "pinout.h"

// FileSystem / SD
#include <FS.h>
#include "LittleFS.h"

// Screen
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>

// Capacitve
#include <XPT2046_Bitbang.h>

class Peripherals{
    public:
        bool fsStatus = false;
        bool sdStatus = false;
        bool videoStatus = false;
        void getMemory();

        void status();
        bool setup();
        String pickRandomFile(String folder);
    private:
        bool screenSetup();
        bool fsSetup();
        bool SDSetup();
        SPIClass spi_sd = SPIClass(VSPI);
        XPT2046_Bitbang ts = XPT2046_Bitbang(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS);
};

#endif