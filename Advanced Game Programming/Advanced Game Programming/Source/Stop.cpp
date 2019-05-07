#include "Stop.h"
#include "Object.h"
#include "Components.h"
#include "BodyComponent.h"
#include "Library.h"
#include "SpriteComponent.h"
#include "TimeDestructComponent.h"
#include "BehaviorComponent2.h"
#include "RayCast.h"
#include "PhysicsDevice.h"
#include "BehaviorTree.h"

Stop::Stop() {}

Stop::Stop(BehaviorTree* tree, Task* control) : LeafTask(tree, control) {
	self = tree->getOwner();
}

Stop::~Stop() {}

bool Stop::Initialize(bool* conditional) {
	if (conditional != nullptr) {
		this->conditional = conditional;
		return true;
	}
	else {
		return false;
	}
}

// Stop all movement
std::unique_ptr<Object> Stop::run() {
	Position zero;
	zero.x = 0.0f;
	zero.y = 0.0f;
	self->getComponent<BodyComponent>()->setVelocity(zero);
	success();
	return nullptr;
}