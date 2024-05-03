#include "audioPlayer.h"

void Audio::setup(int sclk, int lrck, int dout)
{
    audioLogger = &Serial;
    out = new AudioOutputI2S();
    out->SetGain(0.05);
    out->SetPinout(sclk, lrck, dout);
    mp3 = new AudioGeneratorMP3();
}

void Audio::playFile(String filename)
{
    Serial.println("[🎵 SD] Playing " + filename);
    audioFile = new AudioFileSourceSD(filename.c_str());
    mp3->begin(audioFile, out);
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