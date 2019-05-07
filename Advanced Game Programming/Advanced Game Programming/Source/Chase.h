#pragma once
#ifndef CHASE_H
#define CHASE_H

#include <memory>
#include "LeafTask.h"

class BehaviorTree;
class Object;

class Chase : public LeafTask {
public:
	Chase();
	Chase(BehaviorTree* tree, Task* control);
	~Chase();

	bool Initialize(bool* conditional);

	std::unique_ptr<Object> run();
private:
	bool* conditional;
	Object* self;
};

#endif