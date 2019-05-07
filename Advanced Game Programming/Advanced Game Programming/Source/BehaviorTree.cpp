#include "BehaviorTree.h"
#include "Components.h"
#include "Task.h"
#include "Object.h"

BehaviorTree::BehaviorTree() {
	root = nullptr;
}

BehaviorTree::BehaviorTree(Object* owner) :Task(owner) {
	root = nullptr;
}

BehaviorTree::~BehaviorTree() {
}

void BehaviorTree::reset() {
	root->reset();
}

// Returns enemy arrow object (if arrow has been shot)
std::unique_ptr<Object> BehaviorTree::run() {
	std::unique_ptr<Object> created = nullptr;
	if (root->getStatus() != CANCELLED) {
		if (auto temp = root->run(); temp != nullptr) {
			created = std::move(temp);
		}
		
	}
	return created;
}

bool BehaviorTree::addChildToTask(Task* childTask) {
	if (root == nullptr) {
		root = childTask;
	}
	else {
		return false;
	}
	return true;
}

Task* BehaviorTree::getChild(int index) {
	if (index == 0) {
		return root;
	}
	else {
		return nullptr;
	}
}