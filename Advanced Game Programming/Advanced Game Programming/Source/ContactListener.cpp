#include "ContactListener.h"
#include "Object.h"
#include "Components.h"
#include "Library.h"
#include "BodyComponent.h"

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
		objectB->getOwner()->setIsDead(true);
	}
	if (objectB->getOwner()->getType() == ObjectType::bullet &&
		objectA->getOwner()->getType() == ObjectType::enemy) {
		objectA->getOwner()->setIsDead(true);
	}
}