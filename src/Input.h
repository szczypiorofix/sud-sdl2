#pragma once

#include <SDL2/SDL.h>


class Input {

public:
	Input();
	~Input();

private:

	SDL_Event eventHandler;

};

