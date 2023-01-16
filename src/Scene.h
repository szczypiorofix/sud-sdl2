#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "Spritesheet.h"


class Scene {

public:

	Scene( std::string name, SDL_Renderer* renderer );

	~Scene();


	void load();
	void addSpriteSheet(std::string spriteSheet);

	void draw();

	void unload();

private:

	std::string name;

	SDL_Renderer* renderer;

	Spritesheet* spriteSheet;


};

