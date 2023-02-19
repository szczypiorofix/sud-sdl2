#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Defines.h"
#include "input/Inputs.h"
#include "graphics/Texture.h"
#include "scene/Scene.h"
#include "graphics/Font.h"
#include "graphics/TextureManager.h"
#include "graphics/Vector2D.h"
#include "graphics/Transform.h"
#include "helpers/LuaHandler.h"
#include "audio/Music.h"

#include "scene/UIEvents.h"



namespace SUD {

	const int SCREEN_WIDTH = 1360;
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

		void ReloadLuaScripts();

	private:

		GameSystem(void);

		SUD::Inputs* inputs;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Cursor* cursor;
		Scene* scene;
		LuaHandler* luaHandler;

		Music* music;

		Texture* notoFontTexture;
		Texture* vingueFontTexture;
		Font* notoFont;
		Font* vingueFont;

		bool quitGame;

		void Close( void );

		void InitMainSDLModule( void );
		void InitSDLSettings( void );
		void InitWindow( void );
		void InitRenderer( void );
		void InitGraphics( void );
		void InitLuaState( void );

		void InitMouse( void );

		void InitSFX( void );

		void InitScenes( void );

		void LoadAssets( void );

		void GameLoop( void );

		void Update( double dt );
		void Input( void );
		void Render( void );

		Uint64 startPerf;
		Uint64 endPerf;
		float elapsedMS;
		float delayMS;
		int delayMSCounter;
		
		int delayFrameCounter;
		float fpsSum;

		Uint32 endTicks;
		Uint32 startTicks;

		float _fps;
		float frameTime;

		int FPS;

		bool lockFPS;
		bool vsyncOn;
		
		float targetFPS;

		UI* mm_gui_button;

		// Lua
		int reloadLuaScripts; // 0 - idle, 1 - reloading, 2 - end

	};

}
