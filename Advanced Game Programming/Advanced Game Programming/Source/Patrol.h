#pragma once
#ifndef PATROL_H
#define PATROL_H

#include <memory>
#include "LeafTask.h"

class BehaviorTree;
class Object;

class Patrol : public LeafTask {
public:
	Patrol();
	Patrol(BehaviorTree* tree, Task* control);
	~Patrol();

	bool Initialize(bool* conditional);

	std::unique_ptr<Object> run();
private:
	bool* conditional;
	Object* self;
	int moveCount;
};

#endif