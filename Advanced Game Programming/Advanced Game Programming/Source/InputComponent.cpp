#include "InputComponent.h"
#include "InputDevice.h"
#include "Object.h"
#include "Components.h"
#include "BodyComponent.h"
#include "Library.h"
#include "SpriteComponent.h"
#include "BehaviorComponent2.h"
#include "TimeDestructComponent.h"
#include "PhysicsDevice.h"
#include <iostream>


// Arguments: owner object, library, associated body component
InputComponent::InputComponent(Object* owner, Library* library, BodyComponent* body):
	Components(owner),
	library(library),
	body(body) {
	shotTimer = 0;
}

InputComponent::~InputComponent() {

}

std::unique_ptr<Object> InputComponent::update() {

	//Create new Position to be placed into the body component
	Position pos = body->getPosition();
	body->setAngle(0.0f);
	// Create placeholder object
	std::unique_ptr<Object> bullet = nullptr;

	// Decrement shot timer unless it is 0
	if (shotTimer > 0) {
		shotTimer--;
	}
	else { shotTimer = 0; }

	if (library->iDevice->keyStates[InputDevice::UserInputs::DOWN]) {
		body->setYVelocity(50.0f);
		direction = 0;
		//angle = 180.0f;
	}
	else if (library->iDevice->keyStates[InputDevice::UserInputs::UP]) {
		body->setYVelocity(-50.0);
		direction = 1;
		//angle = 0.0f;
	}
	else {
		body->setVelocity({ body->getLinearVelocity().x, 0.0 });
	}
	if (library->iDevice->keyStates[InputDevice::UserInputs::LEFT]) {
		body->setXVelocity(-50.0);
		direction = 2;
		//angle = 270.0f;
	}
	else if (library->iDevice->keyStates[InputDevice::UserInputs::RIGHT]) {
		body->setXVelocity(50.0);
		direction = 3;
		//angle = 90.0f;
	}
	else {
		body->setVelocity({ 0.0, body->getLinearVelocity().y });
	}
	if (library->iDevice->keyStates[InputDevice::UserInputs::SPACE]) {
		// If shot timer is 0, create a new bullet object
		if (shotTimer == 0) {
			shotTimer = 25;
			BodyInitializer bullBodyInit;
			SpriteInitializer bullSpriteInit;
			switch (direction) {
			case 0:
				bullBodyInit.pos.x = pos.x + 8;
				bullBodyInit.pos.y = pos.y + 26;
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
			bullSpriteInit.spriteName = "sword";
			bullSpriteInit.texture = library->artLibrary["sword"];
			bullSpriteInit.gDevice = library->gDevice;

			bullet = std::make_unique<Object>();
			bullet->setType(ObjectType::bullet);
			bullet->addComponent(new SpriteComponent(bullet.get(), bullSpriteInit));
			bullet->addComponent(new BodyComponent(bullet.get(), library, bullBodyInit));
			bullet->getComponent<SpriteComponent>()->spriteBody = bullet->getComponent<BodyComponent>();
			bullet->addComponent(new BehaviorComponent2(bullet.get(), bullet->getComponent<BodyComponent>(), direction));
			bullet->addComponent(new TimeDestructComponent(bullet.get(), 100));
		}
	}

	return bullet;
}