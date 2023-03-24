#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



namespace SUD {

	class Inputs {

	public:
		Inputs();

		~Inputs();

		void Init( SDL_Window* window, int setMousePositionX, int setMousePositionY, const char* mouseIconImage );

		SDL_Event* event;

	private:
		SDL_Cursor* cursor;
	};

}



