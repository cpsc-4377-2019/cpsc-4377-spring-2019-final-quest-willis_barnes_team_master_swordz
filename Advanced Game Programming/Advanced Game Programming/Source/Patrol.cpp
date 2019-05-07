#include "Patrol.h"
#include "BehaviorTree.h"
#include "BodyComponent.h"
#include "Object.h"

Patrol::Patrol() {}

Patrol::Patrol(BehaviorTree* tree, Task* control) : LeafTask(tree, control) {
	self = tree->getOwner();
	moveCount = 0;
}

Patrol::~Patrol() {}

bool Patrol::Initialize(bool* conditional) {
	if (conditional != nullptr) {
		this->conditional = conditional;
		return true;
	}
	else {
		return false;
	}
}

// Patrols the current area
std::unique_ptr<Object> Patrol::run() {
	BodyComponent* body = self->getComponent<BodyComponent>();
	Position vel;
	if (moveCount < 100) {
		vel.x = 50.0f;
		vel.y = 0.0f;
		body->setVelocity(vel);
		moveCount++;
	}
	else if (moveCount < 200) {
		vel.x = 0.0f;
		vel.y = 50.0f;
		body->setVelocity(vel);
		moveCount++;
	}
	else if (moveCount < 300) {
		vel.x = -50.0f;
		vel.y = 0.0f;
		body->setVelocity(vel);
		moveCount++;
	}
	else if (moveCount < 400) {
		vel.x = 0.0f;
		vel.y = -50.0f;
		body->setVelocity(vel);
		moveCount++;
	}
	else { moveCount = 0; }
	success();
	return nullptr;
}