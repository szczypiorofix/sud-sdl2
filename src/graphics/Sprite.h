#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Sprite {

public:

	Sprite();
	~Sprite( void );


private:

	SDL_Texture* texture;
	SDL_Renderer* renderer;


};

