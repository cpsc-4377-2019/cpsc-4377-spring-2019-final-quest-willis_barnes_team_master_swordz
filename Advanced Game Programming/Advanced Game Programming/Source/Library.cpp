#include <iostream>
#include <vector>

#include "tinyxml2.h"
#include "Library.h"
#include "ObjectFactory.h"
#include "Texture.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "PhysicsDevice.h"
#include "Object.h"
#include "AudioDevice.h"
#include "Sound.h"

// Populate object and art libraries
Library::Library(GraphicsDevice* gDevice, InputDevice* iDevice, PhysicsDevice* pDevice, AudioDevice* aDevice) :
	gDevice(gDevice),
	iDevice(iDevice),
	pDevice(pDevice),
	aDevice(aDevice) {

	tinyxml2::XMLDocument doc;

	// Load assets XML file
	if (doc.LoadFile("Assets/Assets.xml") != tinyxml2::XML_SUCCESS) {
		printf("Bad File Path");
		exit(1);
	}

	tinyxml2::XMLElement* root = doc.FirstChildElement("Assets");

	if (!root) {
		printf("Error");
	}

	// Populate artLibrary map with sprites
	for (tinyxml2::XMLElement* element = root->FirstChildElement("Sprites")->FirstChildElement("Sprite"); element; element = element->NextSiblingElement("Sprite")) {
		artLibrary[element->Attribute("name")] = std::make_shared<Texture>(gDevice, element->Attribute("path"));
	}

	// Populate SFXLibrary with sounds
	for (tinyxml2::XMLElement* element = root->FirstChildElement("Sounds")->FirstChildElement("Sound"); element; element = element->NextSiblingElement("Sound")) {
		SFXLibrary[element->Attribute("name")] = std::make_unique<SoundEffect>(element->Attribute("path"), aDevice);
	}

	// Populate musicLibrary with songs
	for (tinyxml2::XMLElement* element = root->FirstChildElement("Songs")->FirstChildElement("Song"); element; element = element->NextSiblingElement("Song")) {
		musicLibrary[element->Attribute("name")] = std::make_unique<BackgroundMusic>(element->Attribute("path"), aDevice);
	}
}

Library::~Library() {
	artLibrary.clear();
}

void Library::addObject(std::unique_ptr<Object>) {

}

std::vector<Object*> Library::getObjects(ObjectType type) {
	std::vector<Object*> objectGet;


	return objectGet;
}