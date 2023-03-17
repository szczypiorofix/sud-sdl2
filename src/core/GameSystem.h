#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


#include "Defines.h"
#include "Window.h"
#include "input/Inputs.h"
#include "scene/Scene.h"
#include "graphics/Font.h"
#include "graphics/TextureManager.h"
#include "lua/LuaHandler.h"
#include "audio/Music.h"



namespace SUD {

	class GameSystem {

	public:

		static GameSystem* GetInstance() {
			static GameSystem* gameSystem = nullptr;
			if ( gameSystem == nullptr ) {
				gameSystem = new GameSystem();
			}
			return gameSystem;
		}

		void Start( int argc, char* args[] );

		SDL_Renderer* GetRenderer();

		void LoadLuaScripts();

	private:

		GameSystem(void);

		SUD::Inputs* inputs;
		Window* window;
		SDL_Renderer* renderer;
		
		Scene* scene;
		LUA::LuaHandler* luaHandler;

		Music* music;

		Texture* notoFontTexture;
		Texture* vingueFontTexture;
		Font* notoFont;
		Font* vingueFont;

		bool quitGame;

		
		
		
		void CloseWindow( void );

		void InitSubsystems( void );





		void InitMainSDLModule( void );
		void InitSDLSettings( void );
		void InitWindow( void );
		void InitRenderer( void );
		void InitGraphics( void );
		void InitLuaHandler( void );

		void InitInputs( void );

		void InitSFX( void );

		void InitScenes( void );

		void LoadAssets( void );

		void StartGameLoop( void );

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

		float fps;
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

		LUA::Object::Game* game;

		std::wstring levelDetails;

	};

}
