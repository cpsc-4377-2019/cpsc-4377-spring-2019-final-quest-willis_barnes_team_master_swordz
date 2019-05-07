#include "BehaviorComponent2.h"
#include "Object.h"
#include "TimeDestructComponent.h"
#include "BodyComponent.h"

// Arguments: owner object, associated body component, direction of movement 
// (0 = down; 1 = up; 2 = left; 3 = right)
BehaviorComponent2::BehaviorComponent2(Object* owner, BodyComponent* body, int direction) : 
	Components(owner),
	body(body),
	direction(direction){

	// Set angle and velocity for body object based on direction
	switch (direction) {
	case 0:
		body->setAngle(90.0f);
		body->setXVelocity(0.0f);
		body->setYVelocity(100.0f);
		break;
	case 1:
		body->setAngle(270.0f);
		body->setXVelocity(0.0f);
		body->setYVelocity(-100.0f);
		break;
	case 2:
		body->setAngle(180.0f);
		body->setXVelocity(-100.0f);
		body->setYVelocity(0.0f);
		break;
	case 3:
		body->setAngle(0.0f);
		body->setXVelocity(100.0f);
		body->setYVelocity(0.0f);
		break;
	}
}

BehaviorComponent2::~BehaviorComponent2() {
	owner = nullptr;
	body = nullptr;
}

std::unique_ptr<Object> BehaviorComponent2::update() {

	return nullptr;
}
