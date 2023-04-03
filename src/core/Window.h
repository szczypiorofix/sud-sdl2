#pragma once

#include <SDL2/SDL.h>


class Window {


public:

	Window( bool _fullScreen );
	~Window();


	void Init( int _width, int _height, const char* name);
	void Input( SDL_Event* _event );
	void Update( double _dt );
	void Destroy();

	SDL_Window* GetWindow();

	bool windowFocusGain;
	bool windowFocusLost;

private:

	SDL_Window* window;

	bool fullScreen;
	
	int width;
	int height;


};

