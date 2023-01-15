#pragma once

#include <stdio.h>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Input.h"


namespace SUD {

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	class GameSystem {

	public:

		GameSystem();
		~GameSystem();
		void launch();
		void close();


	private:

		Input* input;

		SDL_Window* window;

		SDL_Renderer* renderer;

		void initMainSDLModule();
		void initSDLSettings();
		void initWindow();
		void initRenderer();
		void initGraphics();

		void gameLoop();
	};

}
