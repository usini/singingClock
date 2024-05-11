#include "Audio.h"

void Audio::setup(int sclk, int lrck, int dout)
{
    audioLogger = &Serial;
    out = new AudioOutputI2S(0, 0, 16, 0);
    out->SetGain(0.5);
    out->SetPinout(sclk, lrck, dout);
    mp3 = new AudioGeneratorMP3();
}

void Audio::playFile(String filename)
{
    if (!isMute)
    {
        if (isRunning)
        {
            Serial.println("Stop previous file");
            mp3->stop();
        }
        isRunning = true;
        Serial.println("[🎵 SD] Playing " + filename);
        audioFile = new AudioFileSourceSD(filename.c_str());
        mp3->begin(audioFile, out);
    }
}

void Audio::mute()
{
    out->SetGain(0);
    isMute = true;
}

void Audio::unmute()
{
    out->SetGain(0.5);
    isMute = false;
}

void Audio::playStartup()
{

    playFile("/startup.mp3");
}

void Audio::loop()
{
    if (mp3->loop())
    {
    }
    else
    {
        if (isRunning)
        {
            Serial.println("Stopped");
            isRunning = false;
            mp3->stop();
        }
    }
}