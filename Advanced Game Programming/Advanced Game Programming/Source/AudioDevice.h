#pragma once
#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <string>
#include "SDL_mixer.h"

class Library;
class SoundEffect;
class BackgroundMusic;

class AudioDevice {
public:
	AudioDevice();
	~AudioDevice();

	bool playSound(SoundEffect* sound, int numLoops = 1, int channel = -1);

	void setAsBackground(BackgroundMusic* background);

	bool initialized{ false };

private:

	Library* library{ nullptr };
};

#endif