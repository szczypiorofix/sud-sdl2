#pragma once

#include <SDL2/SDL.h>


class Item {


public:

	Item();

	virtual void Draw();
	virtual void Clean();
	virtual void Update(double dt);
	virtual void Input(SDL_Event* event);


};

