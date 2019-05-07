#include "Shoot.h"
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

Shoot::Shoot() {}

Shoot::Shoot(BehaviorTree* tree, Task* control) : LeafTask(tree, control) {
	self = tree->getOwner();
}

Shoot::~Shoot() {}

bool Shoot::Initialize(bool* conditional) {
	if (conditional != nullptr) {
		this->conditional = conditional;
		return true;
	}
	else {
		return false;
	}
}

// Fires an arrow in the player's direction
std::unique_ptr<Object> Shoot::run() {
	std::unique_ptr<Object> bullet = nullptr;

	// Decrement shot timer unless it is 0
	if (shotTimer > 0) {
		shotTimer--;
	}
	else { shotTimer = 0; }

	Position pos = self->getComponent<BodyComponent>()->getPosition();
	Object* player = self->getComponent<BodyComponent>()->getLibrary()->objects[0].get();
	Position playerPos = player->getComponent<BodyComponent>()->getPosition();
	EngineFloat targetAngle = (std::atan2(playerPos.y - pos.y, playerPos.x - pos.x) * 180 / PI);
	if (targetAngle < 0.0f) {
		targetAngle += 360.0f;
	}
	int direction = 0;
	if (targetAngle >= 315.0f || targetAngle < 45.0f) { direction = 3; }
	if (targetAngle >= 45.0f && targetAngle < 135.0f) { direction = 0; }
	if (targetAngle >= 135.0f && targetAngle < 225.0f) { direction = 2; }
	if (targetAngle >= 225.0f && targetAngle < 315.0f) { direction = 1; }

	// If shot timer is 0, create a new bullet object
	if (shotTimer == 0) {
		shotTimer = 50;
		BodyInitializer bullBodyInit;
		SpriteInitializer bullSpriteInit;
		switch (direction) {
		case 0:
			bullBodyInit.pos.x = pos.x + 8;
			bullBodyInit.pos.y = pos.y + 30;
			break;
		case 1:
			bullBodyInit.pos.x = pos.x + 8;
			bullBodyInit.pos.y = pos.y - 10;
			break;
		case 2:
			bullBodyInit.pos.x = pos.x - 10;
			bullBodyInit.pos.y = pos.y + 8;
			break;
		case 3:
			bullBodyInit.pos.x = pos.x + 26;
			bullBodyInit.pos.y = pos.y + 8;
			break;
		}

		bullBodyInit.angle = 0;
		bullBodyInit.physics.bodyType = BodyType::Dynamic;
		bullSpriteInit.spriteName = "arrow";
		Library* library = self->getComponent<BodyComponent>()->getLibrary();
		bullSpriteInit.texture = library->artLibrary["arrow"];
		bullSpriteInit.gDevice = library->gDevice;

		bullet = std::make_unique<Object>();
		bullet->setType(ObjectType::arrow);
		bullet->addComponent(new SpriteComponent(bullet.get(), bullSpriteInit));
		bullet->addComponent(new BodyComponent(bullet.get(), library, bullBodyInit));
		bullet->getComponent<SpriteComponent>()->spriteBody = bullet->getComponent<BodyComponent>();
		bullet->addComponent(new BehaviorComponent2(bullet.get(), bullet->getComponent<BodyComponent>(), direction));
		bullet->addComponent(new TimeDestructComponent(bullet.get(), 100));
		success();
	}
	return bullet;
}