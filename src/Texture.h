#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class Texture {

public:

	Texture( std::string fileName );

	~Texture();



private:

	std::string fileName;

	void load();

};


