#pragma once
#ifndef BEHAVIORCOMPONENT2_H
#define BEHAVIORCOMPONENT2_H

#include <memory>
#include "Components.h"

class Object;
class BodyComponent;

// Controls bullet movement
class BehaviorComponent2 : public Components {
public:
	BehaviorComponent2(Object* owner, BodyComponent* body, int direction);
	~BehaviorComponent2();
	std::unique_ptr<Object> update();
private:
	BodyComponent* body;
	int direction;
};

#endif