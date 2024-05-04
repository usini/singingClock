#include "Audio.h"

void Audio::setup(int sclk, int lrck, int dout)
{
    audioLogger = &Serial;
    out = new AudioOutputI2S();
    out->SetGain(0.5);
    out->SetPinout(sclk, lrck, dout);
    mp3 = new AudioGeneratorMP3();
}

void Audio::playFile(String filename)
{
    if(mp3->isRunning()){
        mp3->stop();
    }
    Serial.println("[🎵 SD] Playing " + filename);
    audioFile = new AudioFileSourceSD(filename.c_str());
    mp3->begin(audioFile, out);
}

void Audio::mute()
{
    out->SetGain(0);
}

void Audio::unmute()
{
    out->SetGain(0.5);
}

void Audio::playStartup()
{
    playFile("/startup.mp3");
}

void Audio::loop()
{
    if (mp3->isRunning())
    {
        mp3->loop();
    }
}