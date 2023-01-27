#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class Spritesheet {

public:

	Spritesheet(std::string fileName, SDL_Renderer* renderer, int tileWidth, int tileHeight);
	~Spritesheet( void );

	void Load( void );

	void Draw( void );

	void Unload( void );

private:
	std::string fileName;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	int tileWidth;
	int tileHeight;
	int tilesX;
	int tilesY;
	int textureWidth;
	int textureHeight;

};

