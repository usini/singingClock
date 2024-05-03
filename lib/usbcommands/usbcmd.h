void cmdUnrecognized(SerialCommands *sender, const char *cmd)
{
    sender->GetSerial()->println("Unrecognized command - " + String(cmd));
}

void cmdStatus(SerialCommands *sender)
{
    peripherals.status();
}

void cmdReboot(SerialCommands *sender)
{
    Serial.println("Rebooting...");
    ESP.restart();
}

void cmdGetTime(SerialCommands *sender)
{
    //Serial.println("[⏲️TIME] - " + myTz.dateTime("H:i"));
    //rtc.dateTime();
    time_t utc = now();
    time_t local = myTZ.toLocal(utc, &tcr);
    int hours = hour(local);
    int minutes = minute(local);

    char formattedTime[6];
    sprintf(formattedTime, "%02d:%02d", hours, minutes);
    Serial.println("[⏲️TIME] - " + timeToString(false));
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
    rtc.adjust(serialTimeToDateTime(time));
    setSyncProvider(rtcToTime_T);
    Serial.println("[⏲️TIME] - " + timeToString(false));
}
