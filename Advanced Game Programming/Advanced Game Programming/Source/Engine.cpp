#include <iostream>
#include <memory>
#include "Engine.h"
#include "Library.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Timer.h"
#include "View.h"
#include "Texture.h"
#include "Definitions.h"
#include "Components.h"
#include "BodyComponent.h"
#include "TimeDestructComponent.h"
#include "PhysicsDevice.h"

Engine::Engine() {
	factory = std::make_unique<ObjectFactory>();
	// Construct and initialize graphics device
	gDevice = std::make_unique<GraphicsDevice>(800, 600);
	if (!gDevice->Initialize(true)) {
		printf("Graphics Device could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	view = std::make_shared<View>(gDevice->getRenderer(), gDevice->getScreenWidth(), gDevice->getScreenHeight());
	gDevice->setView(view);
	// Construct input device
	iDevice = std::make_unique<InputDevice>();
	if (!iDevice) {
		printf("Input Device could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	pDevice = std::make_unique<PhysicsDevice>();
	if (!pDevice) {
		printf("Physics Device could not initialize!");
		exit(1);
	}

	// Construct library and load first level
	gameLibrary = std::make_unique<Library>(gDevice.get(), iDevice.get(), pDevice.get());
	loadLevel("Assets/levelOne.xml");

}

Engine::~Engine() {
	gameLibrary = nullptr;
	gDevice->ShutDown();
	gDevice = nullptr;
	pDevice = nullptr;
	iDevice = nullptr;
	pDevice = nullptr;
	view = nullptr;
	timer = nullptr;
}

// Load level from XML (Argument: path to XML file)
void Engine::loadLevel(std::string levelPath) {
	tinyxml2::XMLDocument doc;

	factory->resetEnemyCount();
	// Load level XML file
	if (doc.LoadFile(levelPath.c_str()) != tinyxml2::XML_SUCCESS) {
		printf("Bad File Path");
		exit(1);
	}

	tinyxml2::XMLElement* root = doc.FirstChildElement("Level");

	if (!root) {
		printf("Error");
	}

	// Populate object vector with objects based on the level XML file
	for (tinyxml2::XMLElement* element = root->FirstChildElement("Object"); element; element = element->NextSiblingElement("Object")) {
		gameLibrary->objects.push_back(factory->create(element, gameLibrary.get()));
	}
	levelSwitchThreshold = gameLibrary->objects.size() - factory->getEnemyCount();
	std::cout << levelSwitchThreshold;
}

// Save level to XML (Argument: path to XML file)
void Engine::saveLevel(std::string levelPath) {
	tinyxml2::XMLDocument doc;

	// Load XML file for level
	if (doc.LoadFile(levelPath.c_str()) != tinyxml2::XML_SUCCESS) {
		printf("Bad File Path");
		exit(1);
	}

	tinyxml2::XMLElement* root = doc.FirstChildElement("Level");

	if (!root) {
		printf("Error");
	}

	tinyxml2::XMLElement* objectElement = root->FirstChildElement("Object");

	// Get current stats for each object in the object vector and set the corresponding XML elements
	// with the new stats
	/*for (auto& object : objects)
	{
		tinyxml2::XMLElement* body = objectElement->FirstChildElement("Body");
		body->SetAttribute("x", object->getComponent<BodyComponent>()->getX());
		body->SetAttribute("y", object->getComponent<BodyComponent>()->getY());
		body->SetAttribute("angle", object->getComponent<BodyComponent>()->getAngle());
		objectElement = objectElement->NextSiblingElement("Object");
	}*/

	// Save updated elements to the XML file.
	doc.SaveFile(levelPath.c_str());
}

// Update the input device, objects, and view
void Engine::update() {
	// Get new user inputs
	iDevice->update();

	// Check if new objects were created in last cycle and add to object vector
	if (!tempObjects.empty()) {
		for (auto& object : tempObjects) {
			gameLibrary->objects.push_back(std::move(object));
		}
	}
	tempObjects.erase(tempObjects.begin(), tempObjects.end());

	if (gameLibrary->objects.size() <= levelSwitchThreshold) {
		gameLibrary->objects.clear();
		loadLevel("Assets/levelTwo.xml");
		std::cout << "Loading level 2";
	}

	// Update each object in vector. Add new objects to tempObjects vector to be added
	// to object vector in next cycle
	for (auto object = gameLibrary->objects.begin(); object != gameLibrary->objects.end();) {
		if (auto temp = (*object)->update(); temp != nullptr) {
			tempObjects.push_back(std::move(temp));
		}

		// If TimeDestructComponent timer has expired, set object as dead
		if ((*object)->getComponent<TimeDestructComponent>() != nullptr &&
			(*object)->getComponent<TimeDestructComponent>()->timer <= 0) {
			(*object)->setIsDead(true);
		}

		// Erase objects marked as dead
		if ((*object)->getIsDead() == true) {
			pDevice->removeObject((*object)->getComponent<BodyComponent>());
			object = gameLibrary->objects.erase(object);
		}
		else {
			object++;
		}

	}
	pDevice->update(1.0f / 60.0f);
	//Update view based on player position
	Position pos = gameLibrary->objects[0]->getComponent<BodyComponent>()->getPosition();
	view->Update(pos);
	gDevice->setView(view);
}

// Draw the new position of each object to the screen
void Engine::draw() {
	for (std::vector<std::unique_ptr<Object>>::iterator i = gameLibrary->objects.begin(); i != gameLibrary->objects.end(); i++) {
		(*i)->draw(view.get());
	}
}

// The game loop - this runs until the player quits
bool Engine::run() {
	
	// Check if the player has quit
	if (iDevice->keyStates[InputDevice::UserInputs::QUIT]) {
		return false;
	}

	// Set and initialize the framerate timer
	timer = std::make_unique<Timer>();
	if (!timer->Initialize(100)) {
		printf("Frame Timer could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	// Game loop
	gDevice->Begin();
	update();
	timer->fpsRegulate();
	draw();
	gDevice->Present();

	return true;
}

void Engine::reset() {
	view = nullptr;
	gameLibrary->objects.clear();
}