#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



namespace SUD {

	constexpr int Key_Up = 0;
	constexpr int Key_Right = 1;
	constexpr int Key_Down = 2;
	constexpr int Key_Left = 3;

	struct Keys {
		bool keyDown;
	};


	class Inputs {

	public:
		Inputs();

		~Inputs();

		void ResolveInputs();

		void Init( SDL_Window* window, int setMousePositionX, int setMousePositionY, const char* mouseIconImage );

		SDL_Event* event;

		bool windowFocusGain;
		bool windowFocusLost;

		Keys keys[4];

	private:
		SDL_Cursor* cursor;
	};

}



