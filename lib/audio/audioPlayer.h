
#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

class Audio{
    public:
        void setup(int sclk, int lrck, int dout);
        void playFile(String filename);
        void playStartup();
        void loop();
    private:
        AudioGeneratorMP3 *mp3;
        AudioFileSourceSD *audioFile;
        AudioOutputI2S *out;
};

#endif // AUDIO_PLAYER_H