#include "Task.h"
#include "Object.h"

Task::Task() {
	owner = nullptr;
	tree = nullptr;
	control = nullptr;
}

Task::Task(BehaviorTree* tree, Task* control) {
	this->tree = tree;
	this->control = control;
}

Task::Task(Object* owner) {
	this->owner = owner;
}

Task::~Task() {

}

void Task::start() {

}

void Task::end() {

}

void Task::reset() {
	status = FRESH;
}

void Task::running() {
	control->childRunning();
	status = RUNNING;
}

void Task::success() {
	control->childSuccess();
	status = SUCCEEDED;
	end();
}

void Task::fail() {
	control->childFail();
	status = FAILED;
	end();
}

void Task::cancel() {
	if (status == RUNNING) {
		status = CANCELLED;
	}
}

bool Task::addChild(Task* childTask) {
	return (addChildToTask(childTask));
}

Object* Task::getOwner() {
	return owner;
}