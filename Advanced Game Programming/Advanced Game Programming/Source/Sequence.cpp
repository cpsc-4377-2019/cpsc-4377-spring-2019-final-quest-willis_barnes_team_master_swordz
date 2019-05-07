#include "Sequence.h"
#include "Object.h"

Sequence::Sequence() : BranchTask() {

}

Sequence::Sequence(BehaviorTree* tree, Task* control) : BranchTask(tree, control) {

}

Sequence::~Sequence() {

}

std::unique_ptr<Object> Sequence::run() {
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
			if (status == FAILED) break;
		} while (j < children.size() - 1);
	}
	return created;
}

void Sequence::childSuccess() {
	status = SUCCEEDED;
	if (control != nullptr) {
		control->childSuccess();
	}
}

void Sequence::childFail() {
	status = FAILED;
	if (control != nullptr) {
		control->childFail();
	}
}

void Sequence::childRunning() {
	status = RUNNING;
	if (control != nullptr) {
		control->childRunning();
	}
}