#pragma once

#include <SDL2/SDL.h>


namespace SUD {

	class Inputs {

	public:
		Inputs() {
			eventHandler = new SDL_Event();
		}

		~Inputs() {
			eventHandler = nullptr;
		}

		SDL_Event* eventHandler;

	};


	//class Mouse {

	//public:

	//	static int X;
	//	static int Y;

	//	static void Pos(SDL_Event* event) {
	//		if ((*event).type == SDL_MOUSEMOTION) {
	//			SDL_GetMouseState(&X, &X);
	//		}
	//	}

	//};
}



