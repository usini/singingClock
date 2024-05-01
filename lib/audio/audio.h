#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *audioFile;
AudioOutputI2S *out;

void audioInit()
{
    audioLogger = &Serial;
    out = new AudioOutputI2S();
    out->SetGain(0.05);
    out->SetPinout(I2S_SCLK, I2S_LRCK, I2S_DOUT);
    mp3 = new AudioGeneratorMP3();
}

void playFile(String filename)
{
    Serial.println("🎵 Playing " + filename);
    audioFile = new AudioFileSourceSD(filename.c_str());
    mp3->begin(audioFile, out);
}

void playStartup()
{
    playFile("/startup.mp3");
}

void mp3Loop()
{
    if (mp3->isRunning())
    {
        if (!mp3->loop())
        {
            mp3->stop();
        }
    }
}