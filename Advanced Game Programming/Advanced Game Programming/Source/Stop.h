#pragma once
#ifndef STOP_H
#define STOP_H

#include <memory>
#include "LeafTask.h"

class BehaviorTree;
class Object;

class Stop : public LeafTask {
public:
	Stop();
	Stop(BehaviorTree* tree, Task* control);
	~Stop();

	bool Initialize(bool* conditional);

	std::unique_ptr<Object> run();
private:
	bool* conditional;
	Object* self;
};

#endif