#include "View.h"
#include "GraphicsDevice.h"
#include "Definitions.h"
#include "SDL.h"
#include <iostream>


// Set initial values for SDL_Rect viewport and initialize view
View::View(SDL_Renderer* renderer, int w, int h) {
	this->renderer = renderer;
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.w = w;
	viewport.h = h;

	SDL_RenderSetViewport(renderer, &viewport);
}

// TODO: update view position based on player position (view moves when player approaches the edge of the screen)
bool View::Update(Position pos) {

	/*iewport.x = pos.x - viewport.w / 2.0f;
	viewport.y = pos.y - viewport.h / 2.0f;
	
	if (viewport.x < 0)
		viewport.x = 0;
	if (viewport.y < 0) 
		viewport.y = 0;*/

	//Debug
	//std::cout << viewport.x << ", " << viewport.y << "\t" << pos.x << ", " << pos.y << "\n";

	SDL_RenderSetClipRect(renderer, &viewport);
	return true;
}