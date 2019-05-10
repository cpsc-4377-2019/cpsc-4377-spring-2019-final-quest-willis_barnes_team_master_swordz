#include "SDL_Mixer.h"

#include "Sound.h"
#include "AudioDevice.h"

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(effect);
}

SoundEffect::SoundEffect(std::string path, AudioDevice* aDevice)
{
	this->aDevice = aDevice;
	effect = Mix_LoadWAV(path.c_str());
}

void SoundEffect::playSound(int numLoops)
{
	aDevice->playSound(this, numLoops);
}

BackgroundMusic::~BackgroundMusic()
{
	Mix_FreeMusic(background);
}

BackgroundMusic::BackgroundMusic(std::string path, AudioDevice* aDevice)
{
	this->aDevice = aDevice;
	background = Mix_LoadMUS(path.c_str());
}

void BackgroundMusic::setAsBackground()
{
	aDevice->setAsBackground(this);
}