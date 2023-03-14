#pragma once

#include <SDL2/SDL.h>


class Window {


public:

	Window();
	~Window();


	void Init( int _width, int _height, const char* name);
	
	void Destroy();

	SDL_Window* GetWindow();

private:

	SDL_Window* window;

	int width;
	int height;


};

