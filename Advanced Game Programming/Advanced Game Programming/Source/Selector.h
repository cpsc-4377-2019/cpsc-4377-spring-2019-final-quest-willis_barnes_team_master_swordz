#ifndef SELECTOR_H
#define SELECTOR_H

#include "BranchTask.h"

class Selector : public BranchTask {

public:
	Selector();
	Selector(BehaviorTree* tree, Task* control);
	~Selector();

	std::unique_ptr<Object> run();
	void childSuccess();
	void childFail();
	void childRunning();

protected:

};
#endif
