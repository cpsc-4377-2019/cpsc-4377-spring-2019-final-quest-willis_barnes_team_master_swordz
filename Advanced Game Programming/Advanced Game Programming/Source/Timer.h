/*
	Timer Class taken directly from Mr. Orme's Signature Experience Github repositor
		https://github.com/Mr-Orme/signature.experience.engine/blob/master/Source/Timer.h
*/

#ifndef TIMER_H
#define TIMER_H

#include"SDL.h"
#include"Definitions.h"

class Timer
{
public:
	//Initializes variables
	Timer();
	bool Initialize(EngineInt);

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	EngineInt getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

	//Regulate
	void fpsRegulate();

private:
	//The clock time when the timer started
	EngineInt startTicks;
	EngineFloat mpf; //millisecond per frame

	//The ticks stored when the timer was paused
	EngineInt pausedTicks;

	//The timer status
	bool paused;
	bool started;
};

#endif