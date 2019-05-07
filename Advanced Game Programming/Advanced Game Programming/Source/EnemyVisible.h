#pragma once
#ifndef ENEMYVISIBLE_H
#define ENEMYVISIBLE_H

#include <memory>
#include "LeafTask.h"

class BehaviorTree;
class Object;

class EnemyVisible : public LeafTask {
public:
	EnemyVisible();
	EnemyVisible(BehaviorTree* tree, Task* control);
	~EnemyVisible();

	bool Initialize(bool* conditional);

	std::unique_ptr<Object> run();
private:
	bool* conditional;
	Object* self;
};

#endif