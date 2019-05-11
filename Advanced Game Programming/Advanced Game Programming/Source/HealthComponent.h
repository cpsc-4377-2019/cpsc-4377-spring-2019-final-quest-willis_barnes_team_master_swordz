#pragma once
#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Components.h"

class Object;

class HealthComponent : public Components {
public:
	HealthComponent(Object*);
	~HealthComponent();

	std::unique_ptr<Object> update();

	void takeHit();

private:
	int health;
};

#endif