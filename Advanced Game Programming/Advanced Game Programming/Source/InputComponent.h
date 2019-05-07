#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "Components.h"

class Object;
class InputDevice;
class BodyComponent;
class Library;

class InputComponent: public Components {
public:
	InputComponent(Object*, Library*, BodyComponent*);
	~InputComponent();
	std::unique_ptr<Object> update();
private:
	Library* library;
	BodyComponent* body;
	int shotTimer;
	int direction = 0;
};

#endif