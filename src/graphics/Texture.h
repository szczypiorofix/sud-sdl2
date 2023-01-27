#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class Texture {

public:

	Texture( std::string fileName, SDL_Renderer* renderer );

	~Texture( void );

	void draw( SDL_Rect src, SDL_Rect dest );

	SDL_Texture* texture;

private:

	SDL_Renderer* renderer;

	std::string fileName;

	void Load( void );

};


