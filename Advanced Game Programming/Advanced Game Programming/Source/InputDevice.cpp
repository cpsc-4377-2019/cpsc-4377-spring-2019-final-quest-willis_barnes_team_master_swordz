#include "InputDevice.h"
#include <iostream>
InputDevice::InputDevice() {

	// Create SDL event
	event = std::make_unique<SDL_Event>();
	if (!event) {
		printf("SDL Event could not initialize! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}

	// Set initial values for keyStates map
	keyStates[UserInputs::NA] = false;
	keyStates[UserInputs::DOWN] = false;
	keyStates[UserInputs::UP] = false;
	keyStates[UserInputs::LEFT] = false;
	keyStates[UserInputs::RIGHT] = false;
	keyStates[UserInputs::SPACE] = false;
	keyStates[UserInputs::QUIT] = false;

	update();
}

// Retrieves key states and sends them to the translator, then sets the corresponding keyState map element to true
void InputDevice::update() {
	UserInputs gEvent;
	if (SDL_PollEvent(event.get())) {
		switch (event->type) {
		case SDL_KEYDOWN:
			//keyStates.find(UserInputs::NA)->second = false;
			//translates the SDL even to a game event.
			gEvent = translate();
			keyStates.find(gEvent)->second = true;
			break;
		case SDL_KEYUP:
			//translates the SDL even to a game event.
			gEvent = translate();
			keyStates.find(gEvent)->second = false;
			break;
		case SDL_QUIT:
			keyStates.find(UserInputs::QUIT)->second = true;
			break;
		default:
			break;
		}
	}

}

// Translates raw key state data to enum UserInput
InputDevice::UserInputs InputDevice::translate() {
	switch (event->key.keysym.sym)
	{
	case SDLK_LEFT:
		return UserInputs::LEFT;
		break;
	case SDLK_RIGHT:
		return UserInputs::RIGHT;
		break;
	case SDLK_UP:
		return UserInputs::UP;
		break;
	case SDLK_DOWN:
		return UserInputs::DOWN;
		break;
	case SDLK_SPACE:
		return UserInputs::SPACE;
		break;
	default: 
		return UserInputs::NA;
		break;
	}
}