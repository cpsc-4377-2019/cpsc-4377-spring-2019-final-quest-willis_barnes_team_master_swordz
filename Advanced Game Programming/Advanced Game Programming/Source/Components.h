#pragma once
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <memory>

class Object;

class Components {
public:
	Components() = delete;
	Components(Object*);
	~Components();
	Object* getOwner();
	virtual std::unique_ptr<Object> update() = 0;
protected:
	Object* owner;
};

#endif