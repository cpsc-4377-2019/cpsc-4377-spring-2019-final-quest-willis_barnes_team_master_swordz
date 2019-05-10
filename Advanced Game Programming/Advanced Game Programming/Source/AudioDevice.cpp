#include "SDL_mixer.h"

#include "Library.h"
#include "AudioDevice.h"
#include "Sound.h"

AudioDevice::AudioDevice() {
	//allows for OGG support
	{
		auto flags = MIX_INIT_OGG;
		auto initted = Mix_Init(flags);

		if (initted && flags != flags)
		{
			printf("Mix_Init: Failed to init required ogg and mod support!\n");
			printf("Mix_Init: %s\n", Mix_GetError());
			initialized = false;
		}
	}

	//Load the Mixer subsystem
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("SDL Mixer could not initialize! SDL_Error: %s\n", Mix_GetError());
		initialized = false;
	}

	//Allocate sufficient channels
	Mix_AllocateChannels(100);
	initialized = true;
}

AudioDevice::~AudioDevice() {
	Mix_CloseAudio();
	Mix_Quit();
}

bool AudioDevice::playSound(SoundEffect* sound, int numLoops, int channel) {
	Mix_PlayChannel(channel, sound->effect, numLoops);
	return true;
}

void AudioDevice::setAsBackground(BackgroundMusic * background) {
	if (Mix_PlayMusic(background->background, -1) == -1)
	{
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	}
}