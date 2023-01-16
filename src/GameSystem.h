#pragma once

#include <stdio.h>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Inputs.h"
#include "Texture.h"
#include "Scene.h"


namespace SUD {

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	const std::string APP_NAME = "Single User Dungeon";

	class GameSystem {

	public:

		GameSystem();
		~GameSystem();
		void launch();
		void close();


	private:

		Inputs* inputs;

		SDL_Window* window;

		SDL_Renderer* renderer;

		Scene* scene;

		bool quitGame;

		void initMainSDLModule();
		void initSDLSettings();
		void initWindow();
		void initRenderer();
		void initGraphics();

		void loadAssets();

		void gameLoop();

		void update();
		void input();
		void render();

		void printOK();
	};

}
