#pragma once

#include <SDL2/SDL.h>


class Window {


public:

	Window( bool _fullScreen );
	~Window();


	void Init( int _width, int _height, const char* name);
	
	void Destroy();

	SDL_Window* GetWindow();

private:

	SDL_Window* window;

	bool fullScreen;

	int width;
	int height;


};

