#pragma once
#ifndef TIMEDESTRUCTCOMPONENT_H
#define TIMEDESTRUCTCOMPONENT_H

#include <memory>
#include "Components.h"

class Object;

class TimeDestructComponent: public Components {
public:
	TimeDestructComponent(Object* owner, int timer);
	~TimeDestructComponent();
	std::unique_ptr<Object> update();
	int timer;
};

#endif