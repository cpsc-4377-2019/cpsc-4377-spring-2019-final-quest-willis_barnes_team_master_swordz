/*
	Texture class taken directly from Mr. Orme's Signature Experience Github repository
		https://github.com/Mr-Orme/signature.experience.engine/blob/master/Source/Texture.h
*/
#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"
#include "Definitions.h"
class GraphicsDevice;
class Texture {

public:

	//Loads image at specified path
	Texture(GraphicsDevice* gDevice, std::string pathOrText, bool isSprite = true);

	//Default Contructor
	Texture();

	//Deallocates memory
	~Texture();


	bool load(SDL_Renderer*, std::string);

	//Deallocates texture
	void free();

	//Renders texture at given point

	void draw(SDL_Renderer* renderer, Position position, EngineFloat angle, SDL_Rect* clip = NULL);
	int getWidth() { return width; }
	int getHeight() { return height; }
	//Image dimensions

	bool initialzied{ false };
private:

	int width{ 0 };
	int height{ 0 };
	//The actual hardware texture
	SDL_Texture * sprite{ nullptr };


};

#endif