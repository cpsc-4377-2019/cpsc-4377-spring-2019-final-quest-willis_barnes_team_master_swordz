#pragma once
#ifndef SOUND_H
#define SOUND_H

#include <string>
#include "SDL_mixer.h"

class AudioDevice;

class SoundEffect {
public:
	SoundEffect() = delete;
	~SoundEffect();
	SoundEffect(std::string path, AudioDevice* aDevice);
	void playSound(int numLoops = 1);
	Mix_Chunk * effect{ nullptr };
private:
	AudioDevice* aDevice;
};

class BackgroundMusic {
public:
	BackgroundMusic() = delete;
	~BackgroundMusic();
	BackgroundMusic(std::string path, AudioDevice* aDevice);
	void setAsBackground();
	Mix_Music * background{ nullptr };
private:
	AudioDevice * aDevice;
};
#endif