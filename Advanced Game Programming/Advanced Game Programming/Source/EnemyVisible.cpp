#include "EnemyVisible.h"
#include "Object.h"
#include "BodyComponent.h"
#include "BehaviorTree.h"
#include "Definitions.h"
#include "Library.h"

EnemyVisible::EnemyVisible() {}

EnemyVisible::EnemyVisible(BehaviorTree* tree, Task* control) : LeafTask(tree, control){
	self = tree->getOwner();
}

EnemyVisible::~EnemyVisible() {}

bool EnemyVisible::Initialize(bool* conditional) {
	if (conditional != nullptr) {
		this->conditional = conditional;
		return true;
	}
	else {
		return false;
	}
}


// Succeeds if the player and enemy are within visible range
std::unique_ptr<Object> EnemyVisible::run() {
	BodyComponent* body = self->getComponent<BodyComponent>();
	Position pos = body->getPosition();
	Object* player = body->getLibrary()->objects[0].get();
	Position playerPos = player->getComponent<BodyComponent>()->getPosition();

	float distance = sqrt((pos.x - playerPos.x) * (pos.x - playerPos.x) + (pos.y - playerPos.y) * (pos.y - playerPos.y));

	if (distance < 150.0f && distance >= 75.0f) {
		success();
	}
	else {
		fail();
	}

	return nullptr;
}

