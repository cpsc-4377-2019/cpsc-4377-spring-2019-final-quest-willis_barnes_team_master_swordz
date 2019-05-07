#include "Object.h"
#include "Components.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"

Object::Object() {
	type = ObjectType::other;
	isDead = false;
}

Object::~Object(){
}

bool Object::Initialize() {
	return true;
}

void Object::addComponent(Components* component) {
	components.push_back(std::unique_ptr<Components>(component));
}

std::unique_ptr<Object> Object::update() {
	std::unique_ptr<Object> created = nullptr;
	for (auto& component : components) {
		if (auto temp = component->update(); temp != nullptr) {
			created = std::move(temp);
		}
	}
	return created;
}

void Object::draw(View* view) {
	this->getComponent<SpriteComponent>()->draw(view);
}

ObjectType Object::getType() {
	return type;
}

void Object::setType(ObjectType type) {
	this->type = type;
}

bool Object::getIsDead() {
	return isDead;
}

void Object::setIsDead(bool dead) {
	this->isDead = dead;
}