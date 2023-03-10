#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


#include "Defines.h"
#include "input/Inputs.h"
#include "scene/Scene.h"
#include "graphics/Font.h"
#include "graphics/TextureManager.h"
#include "lua/LuaHandler.h"
#include "audio/Music.h"



namespace SUD {

	const int SCREEN_WIDTH = 1360;
	const int SCREEN_HEIGHT = 768;


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
		void InitLuaHandler( void );

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

		bool lockedRefreshSettings;

		UI* mm_gui_button;

		// Lua
		bool reloadLuaScripts;
		bool runLuaScriptsOnly;
		//

		LuaGen::Game* game;

		std::wstring levelDetails;

	};

}
