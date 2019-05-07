#ifndef LEAFTASK_H
#define LEAFTASK_H

#include "Task.h"
class LeafTask : public Task {

public:
	LeafTask();
	LeafTask(BehaviorTree* tree, Task* control);
	~LeafTask();

protected:
	void childSuccess(){}
	void childFail(){}
	void childRunning() {}
	bool addChildToTask(Task* childTask) { return false; }
	int getChildCount() { return 0; }
	Task* getChild(int index) { return nullptr; }
};


#endif