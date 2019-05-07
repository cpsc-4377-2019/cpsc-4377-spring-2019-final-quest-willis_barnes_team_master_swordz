#pragma once
#ifndef INRANGE_H
#define INRANGE_H

#include <memory>
#include "LeafTask.h"

class BehaviorTree;
class Object;

class InRange : public LeafTask {
public:
	InRange();
	InRange(BehaviorTree* tree, Task* control);
	~InRange();

	bool Initialize(bool* conditional);

	std::unique_ptr<Object> run();
private:
	bool* conditional;
	Object* self;
};

#endif