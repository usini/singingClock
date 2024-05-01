// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include "timezone.h"
#include <time.h>
#include <TimeLib.h>

time_t rtcToTime_T();

RTC_DS3231 rtc;

TimeChangeRule myDST = {"CEST", Last, Sun, Mar, 2, 120}; // Daylight time = UTC + 2 hours
TimeChangeRule mySTD = {"CET", Last, Sun, Oct, 3, 60};   // Standard time = UTC + 1 hour
Timezone myTZ(myDST, mySTD);
TimeChangeRule *tcr;

int currentHours = 0;
int currentMinutes = 0;
int currentSeconds = 0;


String daysOfTheWeek[7] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};

bool rtcStart()
{
    Wire.begin(27, 22);
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

String timeToString()
{
    time_t utc = now();
    time_t local = myTZ.toLocal(utc, &tcr);
    int hours = hour(local);
    int minutes = minute(local);
    return String(hours) + ":" + String(minutes);
}

String dateToString()
{
    time_t utc = now();
    time_t local = myTZ.toLocal(utc, &tcr);
    String dayString = String(day(local)+1);
    String monthString = String(month(local));
    String dayNameString = daysOfTheWeek[day(local)+1];
    return dayNameString + " " + dayString + "/" + monthString;
}

bool minuteTick(){
    time_t utc = now();
    time_t local = myTZ.toLocal(utc, &tcr);
    int minutes = minute(local);
    int hours = hour(local);
    if(currentMinutes != minutes) {
        currentMinutes = minutes;
        currentHours = hours;
        return true;
    }
    return false;
}

bool hourTick(){
     time_t utc = now();
    time_t local = myTZ.toLocal(utc, &tcr);
    int hours = hour(local);
    if(currentHours != hours) {
        currentHours = hours;
        return true;
    }
    return false;
}