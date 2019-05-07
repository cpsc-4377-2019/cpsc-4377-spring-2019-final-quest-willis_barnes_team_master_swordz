#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H

#include <map>
#include <string>
#include <memory>
#include "Definitions.h"

class ObjectFactory;
class Texture;
class GraphicsDevice;
class InputDevice;
class PhysicsDevice;
class Object;

class Library {
public:
	Library(GraphicsDevice* gDevice, InputDevice* iDevice, PhysicsDevice* pDevice);
	~Library();
	std::map<std::string, std::shared_ptr<Texture>> artLibrary;
	InputDevice* iDevice;
	GraphicsDevice* gDevice;
	PhysicsDevice* pDevice;

	void addObject(std::unique_ptr<Object>);
	std::vector<Object*> getObjects(ObjectType type);

	std::vector<std::unique_ptr<Object>> objects;
};

#endif