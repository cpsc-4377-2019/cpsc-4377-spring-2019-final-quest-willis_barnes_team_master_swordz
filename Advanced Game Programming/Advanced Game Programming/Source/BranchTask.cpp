#include "BranchTask.h"
#include "Object.h"

BranchTask::BranchTask():Task() {

}

BranchTask::BranchTask(BehaviorTree* tree, Task* control):Task(tree, control) {

}

BranchTask::~BranchTask() {

}

std::unique_ptr<Object> BranchTask::run() {
	int i = 0;
	while (i < children.size() && children[i]->getStatus() != RUNNING) {
		i++;
	}
	children[i]->run();
	return nullptr;
}

void BranchTask::reset() {
	for (auto task : children) {
		task->reset();
	}
}

bool BranchTask::addChildToTask(Task* childTask) {
	if (childTask != nullptr) {
		children.push_back(childTask);
		return true;
	}
	return false;
}

int BranchTask::getChildCount() {
	return children.size();
}

Task* BranchTask::getChild(int index) {
	if (index <= getChildCount()) {
		return (children[index]);
	}
	else {
		return nullptr;
	}
}