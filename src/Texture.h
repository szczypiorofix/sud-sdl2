#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class Texture {

public:

	Texture( std::string fileName, SDL_Renderer* renderer );

	~Texture();

	SDL_Texture* texture;

	void draw();

private:

	SDL_Renderer* renderer;

	std::string fileName;

	void load();

};


