#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Defines.h"
#include "Inputs.h"
#include "../graphics/Texture.h"
#include "Scene.h"
#include "../graphics/Font.h"
#include "../graphics/TextureManager.h"
#include "../physics/Vector2D.h"
#include "subsystems/LuaHandler.h"
#include "../physics/Transform.h"



namespace SUD {

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	const std::string APP_NAME = "Single User Dungeon";


	class GameSystem {

	public:

		static GameSystem* GetInstance() {
			static GameSystem* gameSystem = nullptr;
			if ( gameSystem == nullptr ) {
				gameSystem = new GameSystem();
			}
			return gameSystem;
		}

		void Launch( int argc, char* args[] );

		SDL_Renderer* GetRenderer();

	private:

		GameSystem(void);

		SUD::Inputs* inputs;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Cursor* cursor;
		Scene* scene;
		Texture* fontTexture;
		LuaHandler* luaHandler;
		Font* font;

		bool quitGame;

		void Close( void );

		void InitMainSDLModule( void );
		void InitSDLSettings( void );
		void InitWindow( void );
		void InitRenderer( void );
		void InitGraphics( void );
		void InitLuaState( void );

		void InitMouse( void );

		void InitScenes( void );

		void LoadAssets( void );

		void GameLoop( void );

		void Update( double dt );
		void Input( void );
		void Render( void );

		Uint64 startPerf;
		Uint64 endPerf;
		float elapsedMS;

		Uint32 endTicks;
		Uint32 startTicks;

		float fps;
		float frameTime;

		bool lockFPS;
		bool vsyncOn;
		
		float targetFPS;

	};

}
