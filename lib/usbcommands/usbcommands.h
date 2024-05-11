#include <SerialCommands.h>
#include "usbcmd.h"

void serialInit();
void serialLoop();

char usbCommandBuffer[256];
SerialCommands usbCommands(&Serial, usbCommandBuffer,
                            sizeof(usbCommandBuffer), "\r\n", "§");
SerialCommand serialReboot("reboot", cmdReboot);
SerialCommand serialStatus("status", cmdStatus);
SerialCommand serialgetTime("getTime", cmdGetTime);
SerialCommand serialsetTime("setTime", cmdSetTime);

void serialInit()
{
    Serial.begin(115200);
    usbCommands.SetDefaultHandler(cmdUnrecognized);
    usbCommands.AddCommand(&serialReboot);
    usbCommands.AddCommand(&serialStatus);
    usbCommands.AddCommand(&serialgetTime);
    usbCommands.AddCommand(&serialsetTime);
}

void serialLoop()
{
    usbCommands.ReadSerial();
}