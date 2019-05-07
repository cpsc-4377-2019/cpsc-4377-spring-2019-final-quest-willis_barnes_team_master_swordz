#pragma once

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "BranchTask.h"

class Sequence : public BranchTask {

public:
	Sequence();
	Sequence(BehaviorTree* tree, Task* control);
	~Sequence();

	std::unique_ptr<Object> run();
	void childSuccess();
	void childFail();
	void childRunning();

protected:

};



#endif