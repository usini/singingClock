#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "pinout.h"
#include "SPI.h"
#include "SD.h"

// FileSystem / SD
#include <FS.h>
#include "LittleFS.h"

class Filesystem{
    public:
        bool fsStatus = false;
        bool sdStatus = false;
        void getMemory();
        void status();
        bool setup();
        String pickRandomFile(String folder);
    private:
        SPIClass spi_sd = SPIClass(VSPI);
        bool fsSetup();
        bool SDSetup();
};

#endif //FILESYSTEM_H