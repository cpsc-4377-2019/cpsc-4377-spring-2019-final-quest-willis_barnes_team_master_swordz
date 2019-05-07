#include "Chase.h"
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

Chase::Chase() {}

Chase::Chase(BehaviorTree* tree, Task* control) : LeafTask(tree, control){
	self = tree->getOwner();
}

Chase::~Chase() {}

bool Chase::Initialize(bool* conditional) {
	if (conditional != nullptr) {
		this->conditional = conditional;
		return true;
	}
	else {
		return false;
	}
}

std::unique_ptr<Object> Chase::run() {
	// Initialize position with current body component position
	BodyComponent* body = self->getComponent<BodyComponent>();
	Position newPos = body->getPosition();
	body->setAngle(0.0f);

	Object* player = body->getLibrary()->objects[0].get();
	Position playerPos = player->getComponent<BodyComponent>()->getPosition();
	EngineFloat targetAngle = (std::atan2(playerPos.y - newPos.y, playerPos.x - newPos.x) * 180 / PI);
	if (targetAngle < 0.0f) {
		targetAngle += 360.0f;
	}

	Position diff;
	diff.x = std::cos(targetAngle)*50.0f;
	diff.y = std::sin(targetAngle)*50.0f;

	Object* seen = body->getLibrary()->pDevice->RayCast(body, diff);
	if (seen) {
		Position avoidance = diff - seen->getComponent<BodyComponent>()->getPosition();
		float mag = sqrt(avoidance.x * avoidance.x + avoidance.y * avoidance.y);
		avoidance.x /= mag;
		avoidance.x *= 10.0f;
		avoidance.y /= mag;
		avoidance.y *= 10.0f;
		diff = diff + avoidance;
		seen = body->getLibrary()->pDevice->RayCast(body, diff);
	}

	body->setVelocity(diff);
	success();
	return nullptr;
}