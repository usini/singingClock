// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

time_t rtcToTime_T();

RTC_DS3231 rtc;

bool rtcStart()
{
    Wire.begin(I2C_SDA, I2C_SCL);
    if (!rtc.begin(&Wire))
    {
        if (rtc.lostPower())
        {
            Serial.println("RTC lost power, let's set the time!");
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
        return false;
    }
    else
    {
        Serial.println("RTC OK");
        setSyncProvider(rtcToTime_T);
        if (timeStatus() != timeSet)
        {
            Serial.println("Unable to sync with the RTC");
            return false;
        }
        else
        {
            Serial.println("RTC has set the system time");
            return false;
        }
    }
}

time_t rtcToTime_T()
{
    DateTime now = rtc.now(); // Obtenir l'heure actuelle de RTC

    // Créer une structure tm
    struct tm t;
    t.tm_year = now.year() - 1900; // Année depuis 1900
    t.tm_mon = now.month() - 1;    // Mois depuis janvier (0-11)
    t.tm_mday = now.day();         // Jour du mois (1-31)
    t.tm_hour = now.hour();        // Heures (0-23)
    t.tm_min = now.minute();       // Minutes (0-59)
    t.tm_sec = now.second();       // Secondes (0-59)
    t.tm_isdst = -1;               // -1 signifie que la détection automatique de l'heure d'été est activée

    // Convertir la structure tm en time_t
    time_t epoch_time = mktime(&t);
    return epoch_time;
}

bool minuteTick()
{
    time_t local = getLocalTime();
    int minutes = minute(local);
    int hours = hour(local);
    if (currentMinutes != minutes)
    {
        currentMinutes = minutes;
        currentHours = hours;
        return true;
    }
    return false;
}

bool hourTick()
{
    time_t utc = now();
    time_t local = myTZ.toLocal(utc, &tcr);
    int hours = hour(local);
    if (currentHours != hours)
    {
        currentHours = hours;
        return true;
    }
    return false;
}

DateTime serialTimeToDateTime(int time[])
{
    return DateTime(time[5], time[4], time[3], time[0], time[1], time[2]);
}