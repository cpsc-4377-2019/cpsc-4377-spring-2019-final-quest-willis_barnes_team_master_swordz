#include "TimeDestructComponent.h"
#include "Object.h"

// Arguments: owner object, frames until destruct
TimeDestructComponent::TimeDestructComponent(Object* owner, int timer) : 
	Components(owner),
	timer(timer){}

TimeDestructComponent::~TimeDestructComponent() {}

std::unique_ptr<Object> TimeDestructComponent::update() {
	timer--;
	return nullptr;
}