#include "SpriteComponent.h"
#include "Library.h"
#include "Object.h"
#include "View.h"
#include "GraphicsDevice.h"
#include "Engine.h"

// Arguments: owner object, component initializers
SpriteComponent::SpriteComponent(Object* owner, SpriteInitializer spriteInit) :Components(owner) {
	this->texture = spriteInit.texture;
	this->spriteBody = owner->getComponent<BodyComponent>();
	this->gDevice = spriteInit.gDevice;
}

SpriteComponent::~SpriteComponent() {
	if (sprite) {
		sprite->~SpriteComponent();
	}
}

void SpriteComponent::draw(View* view) {

	Position updatedPosition;

	updatedPosition.x = spriteBody->getX() - view->viewport.x;
	updatedPosition.y = spriteBody->getY() - view->viewport.y;



	texture->draw(gDevice->getRenderer(), updatedPosition, spriteBody->getAngle(), NULL);

	//updatedPosition = getViewAdjustedPosition();

	////TODO: add getComponent method to Object class
	//auto angle = getAngle(owner->getComponent<BodyComponent>);
	//EngineFloat angle = 0;
	//draw(updatedPosition, angle);

	//if (sprite) {
	//	sprite->draw();
	//}
}

void SpriteComponent::draw(Position pos, EngineFloat angle) {
	texture->draw(gDevice->getRenderer(), pos, 0, NULL);
}

std::unique_ptr<Object> SpriteComponent::update()
{
	return nullptr;
}
