#pragma once

#include <SDL2/SDL.h>


class Inputs {

public:
	Inputs();
	~Inputs();

	SDL_Event* eventHandler;

};

