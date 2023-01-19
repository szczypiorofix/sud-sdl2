#pragma once

#include <stdio.h>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Defines.h"
#include "Inputs.h"
#include "Texture.h"
#include "Scene.h"
#include "Font.h"



namespace SUD {

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	const std::string APP_NAME = "Single User Dungeon";

	class GameSystem {

	public:

		GameSystem( void );
		~GameSystem( void );
		void launch( void );
		void close( void );


	private:

		Inputs* inputs;

		SDL_Window* window;

		SDL_Renderer* renderer;

		Scene* scene;

		Texture* fontTexture;

		Font* font;

		bool quitGame;

		void initMainSDLModule( void );
		void initSDLSettings( void );
		void initWindow( void );
		void initRenderer( void );
		void initGraphics( void );

		void loadAssets( void );

		void gameLoop( void );

		void update( void );
		void input( void );
		void render( void );

		void printOK( void );
	};

}
