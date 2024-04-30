unsigned int lastMinute = -1;
unsigned int lastSecond = -1;
unsigned int lastHour = -1;

bool hourTick()
{
    if (lastHour != myTz.hour())
    {
        lastHour = myTz.hour();
        return true;
    }
    return false;
}

bool minuteTick()
{
    if (lastMinute != myTz.minute())
    {
        lastMinute = myTz.minute();
        return true;
    }
    return false;
}

bool secondTick()
{
    if (lastSecond != myTz.second())
    {
        lastSecond = myTz.second();
        return true;
    }
    return false;
}