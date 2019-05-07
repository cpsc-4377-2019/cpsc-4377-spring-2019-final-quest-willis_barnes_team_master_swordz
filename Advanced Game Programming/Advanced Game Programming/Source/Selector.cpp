#include "Selector.h"
#include "Object.h"

Selector::Selector() : BranchTask() {}

Selector::Selector(BehaviorTree* tree, Task* control) : BranchTask(tree, control) {

}

Selector::~Selector() {

}

std::unique_ptr<Object> Selector::run() {
	std::unique_ptr<Object> created = nullptr;
	if (status == RUNNING) {
		BranchTask::run();
	}
	else {
		int j = -1;
		do {
			j++;
			if (auto temp = children[j]->run(); temp != nullptr) {
				created = std::move(temp);
			}
			if (status == SUCCEEDED) break;
		} while (j < children.size() - 1);
	}
	return created;
}

void Selector::childSuccess() {
	status = SUCCEEDED;
	if (owner != nullptr) {
		control->childSuccess();
	}
}

void Selector::childFail() {
	status = FAILED;
	if (owner != nullptr) {
		control->childFail();
	}
}

void Selector::childRunning() {
	status = RUNNING;
	if (owner != nullptr) {
		control->childFail();
	}
}