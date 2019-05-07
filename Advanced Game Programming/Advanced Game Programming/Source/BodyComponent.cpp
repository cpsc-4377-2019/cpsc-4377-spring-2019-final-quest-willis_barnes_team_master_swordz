#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Object.h"
#include "Definitions.h"
#include "Library.h"
#include "PhysicsDevice.h"

BodyComponent::BodyComponent(Object* newObject, Library* library, BodyInitializer bodyInit) : Components(newObject), library(library) {
	this->library->pDevice->createFixture(this, std::move(bodyInit));
}

std::unique_ptr<Object> BodyComponent::update() {
	return nullptr;
}

Position BodyComponent::getPosition() {
	return library->pDevice->getPosition(this);
}

float BodyComponent::getX() {
	return getPosition().x;
}

float BodyComponent::getY() {
	return getPosition().y;
}

float BodyComponent::getAngle() {
	return library->pDevice->getAngle(this);
}

EngineInt BodyComponent::getHeight() {
	return owner->getComponent<SpriteComponent>()->texture->getHeight();
}

EngineInt BodyComponent::getWidth() {
	return owner->getComponent<SpriteComponent>()->texture->getWidth();
}

void BodyComponent::setPosition(Position pos) {
	library->pDevice->setTransform(this, pos, library->pDevice->getAngle(this));
}

void BodyComponent::setAngle(EngineFloat angle) {
	library->pDevice->setAngle(this, angle);
}

void BodyComponent::setVelocity(Position velocity) {
	library->pDevice->setLinearVelocity(this, velocity);
}

void BodyComponent::setXVelocity(EngineFloat xVelocity) {
	library->pDevice->setLinearVelocity(this, { xVelocity, library->pDevice->getLinearVelocity(this).y });
}

void BodyComponent::setYVelocity(EngineFloat yVelocity) {
	library->pDevice->setLinearVelocity(this, {  library->pDevice->getLinearVelocity(this).x, yVelocity });
}

void BodyComponent::setAngularVelocity(EngineFloat velocity) {
	library->pDevice->setAngularVelocity(this, velocity);
}

Position BodyComponent::getLinearVelocity() {
	return library->pDevice->getLinearVelocity(this);
}

Library* BodyComponent::getLibrary() {
	return library;
}