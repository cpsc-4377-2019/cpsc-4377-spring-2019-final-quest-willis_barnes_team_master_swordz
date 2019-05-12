#include "HealthComponent.h"
#include "Library.h"
#include "Object.h"
#include "Components.h"
#include "AudioDevice.h"
#include "Sound.h"
#include "BodyComponent.h"

HealthComponent::HealthComponent(Object* owner) : Components(owner) {
	health = 100;
}

HealthComponent::~HealthComponent() {

}

std::unique_ptr<Object> HealthComponent::update() {
	if (health == 0) {
		owner->getComponent<BodyComponent>()->getLibrary()->aDevice->playSound(owner->getComponent<BodyComponent>()->getLibrary()->SFXLibrary["player_death"].get());
		owner->setIsDead(true);
	}
	return nullptr;
}

void HealthComponent::takeHit() {
	health -= 25;
}