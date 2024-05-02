#include "timezone.h"
#include <time.h>
#include <TimeLib.h>

TimeChangeRule myDST = {"CEST", Last, Sun, Mar, 2, 120}; // Daylight time = UTC + 2 hours
TimeChangeRule mySTD = {"CET", Last, Sun, Oct, 3, 60};   // Standard time = UTC + 1 hour
Timezone myTZ(myDST, mySTD);
TimeChangeRule *tcr;

int currentHours = 0;
int currentMinutes = 0;
int currentSeconds = 0;

String daysOfTheWeek[7] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};


time_t getLocalTime()
{
    time_t utc = now();
    time_t local = myTZ.toLocal(utc, &tcr);
    return local;
}

String timeToString(bool isFilePath)
{
    //@todo Refactor
    time_t local = getLocalTime();
    int hourInt = hour(local);
    int minuteInt = minute(local);
    String hourString = String(hourInt);
    String minuteString = String(minuteInt);
    if (minuteInt < 10)
    {
        minuteString = "0" + minuteString;
    }
    if (hourInt < 10)
    {
        hourString = "0" + hourString;
    }
    if (isFilePath)
    {
        return hourString + "-" + minuteString;
    }
    return hourString + ":" + minuteString;
}

String dateToString()
{
    time_t utc = now();
    time_t local = myTZ.toLocal(utc, &tcr);
    int dayInt = day(local) + 1;
    int monthInt = month(local);
    String dayString = String(dayInt);
    String monthString = String(monthInt);
    if (dayInt < 10)
    {
        dayString = "0" + dayString;
    }
    if (monthInt < 10)
    {
        monthString = "0" + monthString;
    }
    String dayNameString = daysOfTheWeek[day(local) + 1];
    return dayNameString + " " + dayString + "/" + monthString;
}

