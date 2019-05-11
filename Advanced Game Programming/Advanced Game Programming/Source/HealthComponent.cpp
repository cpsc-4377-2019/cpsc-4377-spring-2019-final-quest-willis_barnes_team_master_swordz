#include "HealthComponent.h"
#include "Library.h"
#include "Object.h"
#include "Components.h"

HealthComponent::HealthComponent(Object* owner) : Components(owner) {
	health = 100;
}

HealthComponent::~HealthComponent() {

}

std::unique_ptr<Object> HealthComponent::update() {
	if (health == 0) {
		owner->setIsDead(true);
	}
	return nullptr;
}

void HealthComponent::takeHit() {
	health -= 25;
}