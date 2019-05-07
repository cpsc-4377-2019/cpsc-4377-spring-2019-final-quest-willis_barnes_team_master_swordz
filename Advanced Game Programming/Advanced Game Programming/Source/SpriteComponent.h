#pragma once
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Components.h"
#include "Texture.h"
#include "BodyComponent.h"

class Object;
class GraphicsDevice;
class View;

class SpriteComponent : public Components {
public:
	SpriteComponent(Object* owner, SpriteInitializer);
	~SpriteComponent();
	std::unique_ptr<Object> update() override;
	void draw(View*);
	void draw(Position, EngineFloat);
	std::shared_ptr<Texture> texture{ nullptr };
	std::unique_ptr<SpriteComponent> sprite{ nullptr };
	BodyComponent* spriteBody{ nullptr };
private:
	GraphicsDevice* gDevice{ nullptr };
	Texture* spriteTexture{ nullptr };
};

#endif