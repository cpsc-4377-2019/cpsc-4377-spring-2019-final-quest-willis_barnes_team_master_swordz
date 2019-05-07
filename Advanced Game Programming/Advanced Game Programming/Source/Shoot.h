#pragma once
#ifndef SHOOT_H
#define SHOOT_H

#include <memory>
#include "LeafTask.h"

class BehaviorTree;
class Object;

class Shoot : public LeafTask {
public:
	Shoot();
	Shoot(BehaviorTree* tree, Task* control);
	~Shoot();

	bool Initialize(bool* conditional);

	std::unique_ptr<Object> run();
private:
	bool* conditional;
	Object* self;
	int shotTimer;
};

#endif