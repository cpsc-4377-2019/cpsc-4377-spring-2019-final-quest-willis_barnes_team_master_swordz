#pragma once
#ifndef BODYCOMPONENT_H
#define BODYCOMPONENT_H

#include <memory>
#include <vector>
#include "Components.h"
#include "Definitions.h"
#include "ObjectFactory.h"

class Object;
class Library;

class BodyComponent : public Components {
public:
	BodyComponent(Object*, Library*, BodyInitializer);

	float getX();
	float getY();
	float getAngle();
	EngineInt getHeight();
	EngineInt getWidth();	
	std::unique_ptr<Object> update();

	Position getPosition();
	void setPosition(Position pos);
	void setAngle(EngineFloat angle);
	void setVelocity(Position velocity);
	void setXVelocity(EngineFloat xVelocity);
	void setYVelocity(EngineFloat yVelocity);
	void setAngularVelocity(EngineFloat velocity);

	Position getLinearVelocity();

	Library* getLibrary();

private:
	Position bodyPos;
	EngineFloat angle;
	Library* library;
};


#endif