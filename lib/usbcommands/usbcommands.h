#include <SerialCommands.h>
#include "usbcmd.h"

void serialInit();
void serialLoop();

char usbCommandBuffer[256];
SerialCommands usbCommands(&Serial, usbCommandBuffer,
                               sizeof(usbCommandBuffer), "\r\n", "§");
SerialCommand serialReboot("reboot", cmdReboot);
SerialCommand serialStatus("status", cmdStatus);
//SerialCommand serialSSID("ssid", cmdSSID);
//SerialCommand serialPass("pass", cmdPass);
//SerialCommand serialwifi("wifi", cmdWifi);
SerialCommand serialgetTime("getTime", cmdGetTime);
SerialCommand serialsetTime("setTime", cmdSetTime);

void serialInit()
{
    usbCommands.SetDefaultHandler(cmdUnrecognized);
    usbCommands.AddCommand(&serialReboot);
    usbCommands.AddCommand(&serialStatus);
    //usbCommands.AddCommand(&serialSSID);
    //usbCommands.AddCommand(&serialPass);
    //usbCommands.AddCommand(&serialwifi);
    usbCommands.AddCommand(&serialgetTime);
    usbCommands.AddCommand(&serialsetTime);
}

void serialLoop()
{
    usbCommands.ReadSerial();
}