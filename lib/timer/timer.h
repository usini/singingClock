unsigned long previousMillisMinute = 0; // Pour l'action toutes les minutes
unsigned long previousMillisSecond = 0; // Pour l'action toutes les secondes
const long intervalMinute = 60000;      // 60 000 millisecondes = 1 minute
const long intervalSecond = 1000;       // 1 000 millisecondes = 1 seconde
unsigned long currentMillis = 0;

bool minute_tick()
{
    if (currentMillis - previousMillisMinute >= intervalMinute)
    {
        previousMillisMinute = currentMillis;
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

bool second_tick()
{
    if (currentMillis - previousMillisSecond >= intervalSecond)
    {
        previousMillisSecond = currentMillis;
        return true;
    }
    else
    {
        return false;
    }
    return false;
}