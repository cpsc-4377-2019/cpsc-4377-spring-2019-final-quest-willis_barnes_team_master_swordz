#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <iostream>
#include <memory>
#include "tinyxml2.h"
#include "Definitions.h"
#include <vector>

class Object;
class Texture;
class BodyComponent;
class SpriteComponent;
class Library;
class GraphicsDevice;

class ObjectFactory {
public:
	ObjectFactory();
	~ObjectFactory();

	std::unique_ptr<Object> create(tinyxml2::XMLElement* objectElement, Library* gameLibrary);

	BodyComponent* createBodyComponent(Object*, tinyxml2::XMLElement*, Library*, SpriteComponent*);
	SpriteComponent* createSpriteComponent(Object*, tinyxml2::XMLElement*, Library*);
};

#endif