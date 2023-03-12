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

}



