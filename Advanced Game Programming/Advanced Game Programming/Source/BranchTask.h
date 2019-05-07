#ifndef BRANCHTASK_H
#define BRANCHTASK_H

#include <memory>
#include "Task.h"

class BranchTask : public Task {
public:
	BranchTask();
	BranchTask(BehaviorTree* tree, Task* control);
	~BranchTask();

	std::unique_ptr<Object> run();
	void reset();

protected:
	bool addChildToTask(Task* childTask);
	int getChildCount();
	Task* getChild(int index);
	std::vector<Task*> children;
};



#endif