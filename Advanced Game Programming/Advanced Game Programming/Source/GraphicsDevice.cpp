/*
	Graphics Device class taken directly from Mr. Orme's Signature Experience Github repository
		https://github.com/Mr-Orme/signature.experience.engine/blob/master/Source/GraphicsDevice.h
*/

#include<iostream>
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_mixer.h"
#include "GraphicsDevice.h"
#include "View.h"
#include "Texture.h"
//#include "SoundDevice.h"




GraphicsDevice::GraphicsDevice(Uint32 width, Uint32 height) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{

}


bool GraphicsDevice::Initialize(bool fullScreen)
{

	//initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return(false);
	}

	//initialize SDL_image subsystems
	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError());
		return(false);
	}

	//initialize SDL_ttf subsystems
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_Error: %s\n", TTF_GetError());
		return(false);
	}

	if (!fullScreen)
	{
		//Construct and check window construction
		screen = SDL_CreateWindow("Schlegend of Schmelda",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		screen = SDL_CreateWindow("Schlegend of Schmelda",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	}
	if (screen == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return(false);
	}

	//Construct the renderer
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return(false);
	}

	//set the background color (default)
	SDL_SetRenderDrawColor(renderer, 255, 192, 122, 255);

	//========================================
	//create view
	//========================================

	//view = std::make_shared<View>(getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);

	return(true);

}

bool GraphicsDevice::ShutDown()
{
	//Free the window
	SDL_DestroyWindow(screen);
	screen = nullptr;

	//Free renderer
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;


	//Quit SDL Subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();


	return(true);
}




void GraphicsDevice::Begin()
{
	SDL_RenderClear(renderer);
}

void GraphicsDevice::draw()
{
	//********************************draw overlays*************************************
	int cornerRadius = 3; //radius of curve of message box corners.
	//the text vector holds any messages.
	while (!overlays.empty())
	{

		overlay currOverlay = overlays.back();
		overlays.pop_back();

		//draw the objects
		for (auto object : currOverlay.objects)
		{
			object.first->draw(renderer, object.second, 0, NULL);

		}



		//!!!!!!!!!!!!!!!!!!!!!!!!!!this needs to be elsewhere!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//	EngineInt spheresFound = 0; //number of spheres found
		//	//if we found all the spheres.
		//	if(spheresFound >= 6)
		//	{
		//		ResourceManager* devices = levelExit -> getComponent<BodyComponent>() -> getDevices().get();
		//		//stop the physics on the trapdoor so we can walk onto that square.
		//		devices -> pDevice -> setStopPhysics(levelExit.get());
		//		//get rid of the notice stating we need to find the spheres.
		//		Notice notice = {15, 0, W, ""};
		//		devices -> getNoticesLibrary() -> RemoveAsset(notice);
		//
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	}
	//back to black. . .
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

void GraphicsDevice::Present()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* GraphicsDevice::getRenderer()
{
	return(renderer);
}

View* GraphicsDevice::getView()
{
	return view.get();
}

void GraphicsDevice::setView(std::shared_ptr<View> view)
{
	this->view = view;
}


bool GraphicsDevice::setFont(std::string path, EngineInt size, RGBA color)
{
	font = TTF_OpenFont(path.c_str(), size);
	if (font == nullptr)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	this->color =
	{
		(Uint8)(color.R),
		(Uint8)(color.G),
		(Uint8)(color.B),
		(Uint8)(color.A)
	};

	return(true);

}



////**************************************
////reverses the order of sprites so that the player is on top.
//void GraphicsDevice::ReverseOrder()
////**************************************
//{
//	std::reverse(sprites.begin(), sprites.end());
//}
//**************************************
//draws a filled circle.

void GraphicsDevice::drawOverlay(Position topLeft, Position bottomRight, RGBA boxBackgroundColor, RGBA boxBorderColor, std::map<Texture*, Position> objects)
{
	overlay newOverlay = { topLeft, bottomRight, boxBackgroundColor, boxBorderColor, objects };
	overlays.push_back(newOverlay);
}

EngineFloat GraphicsDevice::Center(EngineFloat centerOn, EngineFloat width)
{


	EngineFloat point = (centerOn - width) / 2;

	return point;
}