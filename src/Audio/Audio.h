
#ifndef AUDIO_H
#define AUDIO_H

#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"


class Audio{
    public:
        void setup(int sclk, int lrck, int dout);
        void playFile(String filename);
        void playStartup();
        void loop();
        void mute();
        void unmute();
    private:
        bool isMute = false;
        bool isRunning = false;
        AudioGeneratorMP3 *mp3;
        AudioFileSourceSD *audioFile;
        AudioOutputI2S *out;
};

#endif // AUDIO_H