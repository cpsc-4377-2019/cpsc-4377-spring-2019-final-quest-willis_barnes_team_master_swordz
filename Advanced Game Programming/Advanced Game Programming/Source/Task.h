#pragma once
#ifndef TASK_H
#define TASK_H

#include <vector>
#include <memory>

class Object;
class BehaviorTree;

class Task {
public:
	
	Task();
	Task(BehaviorTree* tree, Task* control);
	Task(Object* owner);
	~Task();

	virtual std::unique_ptr<Object> run() = 0;
	virtual void childSuccess() = 0;
	virtual void childFail() = 0;
	virtual void childRunning() = 0;

	virtual void start();
	virtual void end();
	virtual void reset();

	void running();
	void success();
	void fail();
	void cancel();
	bool addChild(Task* childTask);
	Object* getOwner();

	enum Status {
		FRESH, RUNNING, FAILED, SUCCEEDED, CANCELLED
	};

	Status getStatus() { return status; }

protected:
	virtual bool addChildToTask(Task* childTask) = 0;
	virtual int getChildCount() = 0;
	virtual Task* getChild(int index) = 0;

	Status status;

	Task* control;
	BehaviorTree* tree;
	Object* owner;
};

#endif