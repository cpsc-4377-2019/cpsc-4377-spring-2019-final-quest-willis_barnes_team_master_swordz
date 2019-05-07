#include "Components.h"
#include "Object.h"

Components::Components(Object* owner): owner(owner) {}

Components::~Components() {
	owner = nullptr;
}

Object* Components::getOwner() {
	return owner;
}

