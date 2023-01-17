#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "Spritesheet.h"


class Scene {

public:

	Scene( std::string name, SDL_Renderer* renderer );

	~Scene( void );


	void load();

	void addSpriteSheet(std::string spriteSheetName, int tileWidth, int tileHeight);


	void draw( void );
	void unload( void );

private:

	std::string name;

	SDL_Renderer* renderer;

	Spritesheet* spriteSheet;


};

