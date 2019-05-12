#include "ContactListener.h"
#include "Object.h"
#include "Components.h"
#include "Library.h"
#include "BodyComponent.h"
#include "HealthComponent.h"
#include "AudioDevice.h"
#include "Sound.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	//Grab the two Physics Bodies involved in the Contact
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	//Cast them to object pointers
	BodyComponent* objectA = static_cast<BodyComponent*>(bodyA->GetUserData());
	BodyComponent* objectB = static_cast<BodyComponent*>(bodyB->GetUserData());

	if (objectA->getOwner()->getType() == ObjectType::bullet ||
		objectA->getOwner()->getType() == ObjectType::arrow) {
		objectA->getOwner()->setIsDead(true);
	}
	if (objectB->getOwner()->getType() == ObjectType::bullet ||
		objectB->getOwner()->getType() == ObjectType::arrow) {
		objectB->getOwner()->setIsDead(true);
	}

 	if (objectA->getOwner()->getType() == ObjectType::bullet &&
		objectB->getOwner()->getType() == ObjectType::enemy) {
		objectB->getLibrary()->aDevice->playSound(objectB->getLibrary()->SFXLibrary["enemy_death"].get());
		objectB->getOwner()->setIsDead(true);
	}
	if (objectB->getOwner()->getType() == ObjectType::bullet &&
		objectA->getOwner()->getType() == ObjectType::enemy) {
		objectA->getLibrary()->aDevice->playSound(objectA->getLibrary()->SFXLibrary["enemy_death"].get());
		objectA->getOwner()->setIsDead(true);
	}
	if (objectA->getOwner()->getType() == ObjectType::arrow &&
		objectB->getOwner()->getType() == ObjectType::player) {
		objectB->getLibrary()->aDevice->playSound(objectB->getLibrary()->SFXLibrary["player_hurt"].get());
		objectB->getOwner()->getComponent<HealthComponent>()->takeHit();
	}
	if (objectA->getOwner()->getType() == ObjectType::player &&
		objectB->getOwner()->getType() == ObjectType::arrow) {
		objectA->getLibrary()->aDevice->playSound(objectA->getLibrary()->SFXLibrary["player_hurt"].get());
		objectA->getOwner()->getComponent<HealthComponent>()->takeHit();
	}
}