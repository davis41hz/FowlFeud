#include "AudioSystem.h"

AudioSystem* AudioSystem::instance = NULL;

AudioSystem& AudioSystem::getInstance() {
    if(instance == NULL) {
        instance = new AudioSystem();
    }
    return *instance;
}

AudioSystem::~AudioSystem() {
    Mix_Quit();
}

AudioSystem::AudioSystem() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // 44.1khz sample rate, 16bit bit depth, stereo, 2048 byte buffer
}

void AudioSystem::playMusic(Mix_Music* song, int timesThrough) { // -1 is looping, music is used for large files
    Mix_PlayMusic(song, timesThrough);
}

void AudioSystem::fadeOutMusic(int time) {
    Mix_FadeOutMusic(time);
}

void AudioSystem::playSoundEffect(std::string fileName, int timesThrough) {
    Mix_PlayChannel(-1, Mix_LoadWAV_RW(SDL_RWFromFile(fileName.c_str(), "rb"), 1), timesThrough); // takes care of freeing resource automatically
}
