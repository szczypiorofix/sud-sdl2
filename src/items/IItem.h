#pragma once

#include <SDL2/SDL.h>
#include <string>


class IItem {
public:
	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(double dt) = 0;
	virtual void Input(SDL_Event* event) = 0;

	int id;
	std::string name;
};

