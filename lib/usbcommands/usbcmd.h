void cmdUnrecognized(SerialCommands *sender, const char *cmd)
{
    sender->GetSerial()->println("Unrecognized command - " + String(cmd));
}

void cmdStatus(SerialCommands *sender)
{
    peripheralsStatus();
    Serial.println("[📶 WIFI] 🏷️ SSID - " + wifiSSID);
    if (connected)
    {
        Serial.println("[📶 WIFI] 🟢 OK");
    }
    else
    {
        Serial.println("[📶 WIFI] 🔴 FAILED");
    }
}

void cmdReboot(SerialCommands *sender)
{
    Serial.println("Rebooting...");
    ESP.restart();
}

void cmdSSID(SerialCommands *sender)
{
    char *value = sender->Next();
    wifiSSID = value;
    Serial.println("[📶 WIFI] 🏷️ SSID Changed to - " + wifiSSID);
}

void cmdGetTime(SerialCommands *sender)
{
    Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
}

void cmdSetTime(SerialCommands *sender)
{
    char *value;
    int time[6];
    for (int i = 0; i < 6; i++)
    {
        value = sender->Next();
        time[i] = String(value).toInt();
    }
    myTz.setTime(time[0], time[1], time[2], time[3], time[4], time[5]);
    Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
}

void cmdPass(SerialCommands *sender)
{
    char *value = sender->Next();
    wifiPassword = value;
    Serial.println("[📶 WIFI] 🏷️ Password Changed");
}

void cmdWifi(SerialCommands *sender)
{
    char *value = sender->Next();
    String arg = String(value);
    if (arg == "restart")
    {
        wifiChange = true;
        Serial.println("[📶 WIFI] ♾️ Restart");
    }
    else
    {
        Serial.println("[🔌USB] - Invalid command: wifi§" + arg);
    }
}