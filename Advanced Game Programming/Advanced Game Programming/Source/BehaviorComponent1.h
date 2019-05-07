#pragma once
#ifndef BEHAVIORCOMPONENT1_H
#define BEHAVIORCOMPONENT1_H

#include <memory>
#include "Components.h"

class Object;
class BodyComponent;
class SteeringBehaviors;
class BehaviorTree;

// Controls basic enemy movement
class BehaviorComponent1: public Components {
public:
	BehaviorComponent1(Object* owner, BodyComponent* body);
	~BehaviorComponent1();
	std::unique_ptr<Object> update();
private:
	int moveCount;
	BodyComponent* body;
	BehaviorTree* tree;
	
};

#endif