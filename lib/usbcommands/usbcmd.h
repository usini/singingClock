void cmdUnrecognized(SerialCommands *sender, const char *cmd)
{
    sender->GetSerial()->println("Unrecognized command - " + String(cmd));
}

void cmdStatus(SerialCommands *sender)
{
    peripheralsStatus();
    
}

void cmdReboot(SerialCommands *sender)
{
    Serial.println("Rebooting...");
    ESP.restart();
}

void cmdGetTime(SerialCommands *sender)
{
    //Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
    //Serial.println("[⏲️TIME] - " + rtc.dateTime("H:i"));
    //rtc.dateTime();
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

    //myTz.setTime(time[0], time[1], time[2], time[3], time[4], time[5]);
    //Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
    rtc.setTime(time[0], time[1], time[2], time[3], time[4], time[5]);
    //Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
}
