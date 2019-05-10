#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H

#include <map>
#include <string>
#include <memory>
#include <vector>
#include "Definitions.h"

class ObjectFactory;
class Texture;
class GraphicsDevice;
class InputDevice;
class PhysicsDevice;
class Object;
class SoundEffect;
class BackgroundMusic;
class AudioDevice;

class Library {
public:
	Library(GraphicsDevice* gDevice, InputDevice* iDevice, PhysicsDevice* pDevice, AudioDevice* aDevice);
	~Library();
	std::map<std::string, std::shared_ptr<Texture>> artLibrary;
	std::map<std::string, std::unique_ptr<SoundEffect>> SFXLibrary;
	std::map<std::string, std::unique_ptr<BackgroundMusic>> musicLibrary;
	InputDevice* iDevice;
	GraphicsDevice* gDevice;
	PhysicsDevice* pDevice;
	AudioDevice* aDevice;

	void addObject(std::unique_ptr<Object> object);
	std::vector<Object*> getObjects(ObjectType type);

	std::vector<std::unique_ptr<Object>> objects;
};

#endif