#pragma once
#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <memory>
#include <map>
#include "SDL.h"
#include "Definitions.h"

class InputDevice {
public:
	InputDevice();
	void update();
	enum class UserInputs
	{
		NA,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SPACE,
		QUIT,
		NUM_EVENTS
	};

	std::map<UserInputs, bool> keyStates;
private:
	UserInputs translate();
	std::unique_ptr<SDL_Event> event{ nullptr };
};

#endif
