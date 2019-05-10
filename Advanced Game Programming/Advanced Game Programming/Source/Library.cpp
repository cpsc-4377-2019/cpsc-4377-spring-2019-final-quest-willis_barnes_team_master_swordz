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

// Populate object and art libraries
Library::Library(GraphicsDevice* gDevice, InputDevice* iDevice, PhysicsDevice* pDevice): 
	gDevice(gDevice), 
	iDevice(iDevice), 
	pDevice(pDevice) {

	tinyxml2::XMLDocument doc;

	// Load assets XML file
	if (doc.LoadFile("Assets/Assets.xml") != tinyxml2::XML_SUCCESS) {
		printf("Bad File Path");
		exit(1);
	}

	tinyxml2::XMLElement* root = doc.FirstChildElement("Sprites");

	if (!root) {
		printf("Error");
	}

	// Populate artLibrary map with sprites
	for (tinyxml2::XMLElement* element = root->FirstChildElement("Sprite"); element; element = element->NextSiblingElement("Sprite")) {
		artLibrary[element->Attribute("name")] = std::make_shared<Texture>(gDevice, element->Attribute("path"));
	}

}

Library::~Library() {
	artLibrary.clear();
}

void Library::addObject(std::unique_ptr<Object> ) {

}

std::vector<Object*> Library::getObjects(ObjectType type) {
	std::vector<Object*> objectGet;
	
	return objectGet;
}