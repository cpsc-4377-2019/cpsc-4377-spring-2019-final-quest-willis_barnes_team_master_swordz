#pragma once
#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include "Definitions.h"
#include "SDL.h"

class GraphicsDevice;

class View {
public:
	View() = delete;
	View(SDL_Renderer*, int, int);
	bool Update(Position);
	SDL_Renderer* renderer;
	SDL_Rect viewport;
};

#endif