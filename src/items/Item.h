#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "IItem.h"


class Item : public IItem {


public:

	Item();

	virtual void Draw();
	virtual void Clean();
	virtual void Update(double dt);
	virtual void Input(SDL_Event* event);

	int id;
	std::string name;


};

