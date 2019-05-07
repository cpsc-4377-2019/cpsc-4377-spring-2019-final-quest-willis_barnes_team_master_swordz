#include "ObjectFactory.h"
#include "Object.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Library.h"
#include "BehaviorComponent1.h"
#include "BehaviorComponent2.h"
#include "Definitions.h"

ObjectFactory::ObjectFactory(){

}

ObjectFactory::~ObjectFactory(){

}

// Arguments: owner object, XML initializer values
BodyComponent* ObjectFactory::createBodyComponent(Object* parent, tinyxml2::XMLElement* element, Library* library, SpriteComponent* sprite = nullptr) {
	BodyInitializer bodyInit;
	//ObjectFactory::Initializers bodyInit;
	element->QueryFloatAttribute("x", &bodyInit.pos.x);
	element->QueryFloatAttribute("y", &bodyInit.pos.y);
	element->QueryFloatAttribute("angle", &bodyInit.angle);

	int bT;
	element->QueryIntAttribute("bodytype", &bT);
	switch (bT) {
	case 0:
		bodyInit.physics.bodyType = BodyType::Static;
		break;
	case 1:
		bodyInit.physics.bodyType = BodyType::Kinematic;
		break;
	case 2:
		bodyInit.physics.bodyType = BodyType::Dynamic;
		break;
	}

	//We only have rectangle bodies at the moment
	bodyInit.physics.bodyShape = BodyShape::Rectangle;
	return new BodyComponent(parent, library, bodyInit);
}

// Arguments: owner object, XML initializer values, library
SpriteComponent* ObjectFactory::createSpriteComponent(Object* parent, tinyxml2::XMLElement* componentElement, Library* gameLibrary) {
	SpriteInitializer spriteInit;
	componentElement->QueryStringAttribute("name", &spriteInit.spriteName);
	spriteInit.texture = gameLibrary->artLibrary[spriteInit.spriteName];
	spriteInit.gDevice = gameLibrary->gDevice;

	return new SpriteComponent(parent, spriteInit);
}

std::unique_ptr<Object> ObjectFactory::create(tinyxml2::XMLElement* element, Library* gameLibrary) {
	std::unique_ptr<Object> newObject = std::make_unique<Object>();
	std::string objectType = element->Attribute("type");

	if (objectType == "player") {
		newObject->setType(ObjectType::player);
	}
	else if (objectType == "moblin" || objectType == "octorok") {
		newObject->setType(ObjectType::enemy);
	}

	for (tinyxml2::XMLElement* componentElement = element->FirstChildElement(); componentElement; componentElement = componentElement->NextSiblingElement()) {
		std::string componentName = componentElement->Attribute("type");
		if (componentName == "body") {
			newObject->addComponent(createBodyComponent(newObject.get(), componentElement, gameLibrary, newObject->getComponent<SpriteComponent>()));
			if (SpriteComponent* sprite = newObject->getComponent<SpriteComponent>(); sprite) {
				sprite->spriteBody = newObject->getComponent<BodyComponent>();
			}
		}
		if (componentName == "sprite") {
			newObject->addComponent(createSpriteComponent(newObject.get(), componentElement, gameLibrary));
		}
		if (componentName == "input") {
			newObject->addComponent(new InputComponent(newObject.get(), gameLibrary, newObject->getComponent<BodyComponent>()));
		}
		if (componentName == "behavior1") {
			newObject->addComponent(new BehaviorComponent1(newObject.get(), newObject->getComponent<BodyComponent>()));
		}
	}

	return newObject;
}