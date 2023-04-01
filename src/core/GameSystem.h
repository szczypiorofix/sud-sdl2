#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "Defines.h"
#include "Window.h"
#include "../input/Inputs.h"
#include "../scene/Scene.h"
#include "../graphics/Font.h"
#include "../graphics/TextureManager.h"
#include "../lua/LuaHandler.h"
#include "../audio/Music.h"
#include "../scene/Level.h"



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
		LuaHandler* luaHandler;

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



		const short TARGET_FPS = 50;
		const float OPTIMAL_TIME = 1000.0f / TARGET_FPS;

		long lastTime;
		double delta;
		long timer;
		int updates;
		int frames;
		long now;
		float amountOfTicks;
		int fps_count;
		int ticks_count;
		double ns;
		bool fpsCap;

		bool lockFPS;
		bool vsyncOn;
		bool fullScreen;

		bool lockedRefreshSettings;

		UI* mm_gui_button;

		// Lua
		bool reloadLuaScripts;
		bool runLuaScriptsOnly;
		//

		LuaGame* game;

		std::wstring levelDetails;

		Level* level;

	};

}
