#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class Spritesheet {

public:

	Spritesheet( std::string fileName, SDL_Renderer* renderer );
	~Spritesheet();

	void load();

	void draw();

	void unload();

private:
	std::string fileName;
	SDL_Texture* texture;
	SDL_Renderer* renderer;

};

