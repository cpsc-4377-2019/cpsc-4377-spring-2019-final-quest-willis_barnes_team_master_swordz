#pragma once
#ifndef BEHAVIORTREE_H
#define BEHAVIORTREE_H

#include <memory>
#include "Task.h"

class Object;

class BehaviorTree : public Task {
public:
	BehaviorTree();
	BehaviorTree(Object* owner);
	~BehaviorTree();

	void reset();

	std::unique_ptr<Object> run();
	void childSuccess() { status = SUCCEEDED; };
	void childFail() { status = FAILED; };
	void childRunning() { status = RUNNING; };

protected:
	bool addChildToTask(Task* childTask);
	int getChildCount() { return 1; }
	Task* getChild(int index);

	Task* root;
};

#endif