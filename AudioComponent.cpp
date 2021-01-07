#include "AudioComponent.h"

AudioComponent::AudioComponent(){
    lastSound = NULL;
}

AudioComponent::~AudioComponent() {
    // Mix_FreeChunk(lastSound);
}

void AudioComponent::playSFX(std::string fileName) {
    AudioSystem::getInstance().playSoundEffect(fileName, 0);
}
