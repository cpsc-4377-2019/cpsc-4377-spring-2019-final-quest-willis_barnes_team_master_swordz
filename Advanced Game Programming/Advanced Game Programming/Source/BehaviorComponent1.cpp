#include "BehaviorComponent1.h"
#include "BodyComponent.h"
#include "Object.h"
#include "PhysicsDevice.h"
#include "Library.h"
#include "Stop.h"
#include "Task.h"
#include "Patrol.h"
#include "Shoot.h"
#include "Chase.h"
#include "EnemyVisible.h"
#include "InRange.h"
#include "BehaviorTree.h"
#include "Selector.h"
#include "Sequence.h"

// Arguments: owner object and associated body component
BehaviorComponent1::BehaviorComponent1(Object* owner, BodyComponent* body) :
	Components(owner),
	body(body) {
	tree = new BehaviorTree(this->getOwner());

	Selector* decideBehavior = new Selector(tree, nullptr);
	tree->addChild(decideBehavior);

	Sequence* engagePlayer = new Sequence(tree, decideBehavior);
	decideBehavior->addChild(engagePlayer);
	EnemyVisible* visible = new EnemyVisible(tree, engagePlayer);
	engagePlayer->addChild(visible);
	Chase* chasePlayer = new Chase(tree, engagePlayer);
	engagePlayer->addChild(chasePlayer);

	Sequence* shootAtPlayer = new Sequence(tree, decideBehavior);
	decideBehavior->addChild(shootAtPlayer);

	InRange* enemyInRange = new InRange(tree, shootAtPlayer);
	shootAtPlayer->addChild(enemyInRange);
	Stop* stopMoving = new Stop(tree, shootAtPlayer);
	shootAtPlayer->addChild(stopMoving);
	Shoot* shootPlayer = new Shoot(tree, shootAtPlayer);
	shootAtPlayer->addChild(shootPlayer);

	Sequence* wander = new Sequence(tree, decideBehavior);
	decideBehavior->addChild(wander);

	Patrol* patrol = new Patrol(tree, wander);
	wander->addChild(patrol);
}

BehaviorComponent1::~BehaviorComponent1() {
	owner = nullptr;
	body = nullptr;
}

std::unique_ptr<Object> BehaviorComponent1::update() {
	
	std::unique_ptr<Object> arrowed;

	if (auto temp = tree->run(); temp != nullptr) {
		arrowed = std::move(temp);
	}

	return arrowed;
}
