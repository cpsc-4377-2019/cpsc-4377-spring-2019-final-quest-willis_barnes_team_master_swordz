#include "InRange.h"
#include "Object.h"
#include "BodyComponent.h"
#include "Library.h"
#include "Definitions.h"
#include "BehaviorTree.h"

InRange::InRange() {}

InRange::InRange(BehaviorTree* tree, Task* control) :LeafTask(tree, control){
	self = tree->getOwner();
}

InRange::~InRange() {}

bool InRange::Initialize(bool* conditional) {
	if (conditional != nullptr) {
		this->conditional = conditional;
		return true;
	}
	else {
		return false;
	}
}

// Succeeds if the player and enemy are in range to shoot
std::unique_ptr<Object> InRange::run() {
	BodyComponent* body = self->getComponent<BodyComponent>();
	Position pos = body->getPosition();
	Object* player = body->getLibrary()->objects[0].get();
	Position playerPos = player->getComponent<BodyComponent>()->getPosition();

	float distance = sqrt((pos.x - playerPos.x) * (pos.x - playerPos.x) + (pos.y - playerPos.y) * (pos.y - playerPos.y));

	if (distance < 75.0f) {
		success();
	}
	else {
		fail();
	}

	return nullptr;
}

