#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <memory>
#include <vector>
#include "tinyxml2.h"

class Library;
class Object;
class Timer;
class GraphicsDevice;
class InputDevice;
class View;
class PhysicsDevice;
class AudioDevice;

class Engine {
public:
	Engine();
	~Engine();
	void loadLevel(std::string);
	void saveLevel(std::string);
	void update();
	void draw();
	bool run();
	void reset();

	std::unique_ptr<GraphicsDevice> gDevice{ nullptr };
	std::unique_ptr<InputDevice> iDevice{ nullptr };
	std::unique_ptr<PhysicsDevice> pDevice{ nullptr };
	std::unique_ptr<AudioDevice> aDevice{ nullptr };
	std::unique_ptr<Library> gameLibrary{ nullptr };
	std::unique_ptr<Timer> timer{ nullptr };
	std::shared_ptr<View> view;
	std::vector<std::unique_ptr<Object>> tempObjects;
};

#endif