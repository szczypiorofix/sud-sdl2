#pragma once

#include <SDL2/SDL.h>


class Input {

public:
	Input();
	~Input();

	SDL_Event* eventHandler;

};

