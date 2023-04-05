#include "GameSystem.h"
#include <codecvt>
#include <locale>
#include <sstream>


using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;


namespace SUD {

	GameSystem::GameSystem( void ) {
		renderer = nullptr;
		inputs = nullptr;
		window = nullptr;
		luaHandler = nullptr;
		notoFontTexture = nullptr;
		vingueFontTexture = nullptr;
		notoFont = nullptr;
		vingueFont = nullptr;
		music = nullptr;
		game = nullptr;
		scene = nullptr;
		mm_gui_button = nullptr;
		player = nullptr;
		level = new Level();

		vsyncOn = false;
		fullScreen = false;
		fpsCap = false;

		lockedRefreshSettings = false;
		quitGame = false;

		lastTime = 0L;
		delta = 0.0f;
		timer = 0L;
		updates = 0;
		frames = 0;
		now = 0L;
		amountOfTicks = 60.0;
		fps_count = 0;
		ticks_count = 0;
		ns = 0.0f;

		reloadLuaScripts = false;

		// Run only Lua scripts, without SDL window
		runLuaScriptsOnly = false;
	}


	void GameSystem::Exit( int code ) {
		if (luaHandler != nullptr) {
			luaHandler->Close();
		}
		delete luaHandler;

		if (scene != nullptr) {
			scene->Unload();
		}
		delete scene;

		delete notoFont;
		delete vingueFont;

		delete music;

		delete mm_gui_button;

		TextureManager::GetInstance()->Clean();

		if (renderer != nullptr) {
			SDL_DestroyRenderer(renderer);
		}
		renderer = nullptr;

		if (window != nullptr) {
			window->Destroy();
		}
		delete window;

		IMG_Quit();
		SDL_Quit();

		exit( code );
	}


	void GameSystem::Start(int argc, char* args[]) {
		if (argc > 1) {
			SDL_Log("Game app arguments count: %i\n", argc);
			SDL_Log("Args[0]: %s\n", args[0]);
		}

		InitLuaHandler();
		LoadLuaScripts();

		if (runLuaScriptsOnly) {
			luaHandler->Close();
			Exit(0);
		}

		InitSubsystems();
	}

	void GameSystem::LoadLuaScripts() {
		// LUA SCRIPT

		luaHandler->Close();

		luaHandler->RunScript("main.lua");

		game = luaHandler->GetGame();

		if (game == nullptr) {
			printf("Game object is null. Set game object to default object\n");
			game = new LuaGame("default_game");
		}

		this->fullScreen = game->fullScreen;
		this->fpsCap = game->fpsCap;
		this->amountOfTicks = game->amountOfTicks;
		this->vsyncOn = game->vSync;


		// --- move this somewhere else
		if (renderer != nullptr) {
			SDL_RenderSetVSync(renderer, this->vsyncOn);
		}
		// ---

		LuaPlayer* luaPlayer = luaHandler->GetPlayer();

		if (luaPlayer == nullptr) {
			printf("ERROR: LuaPlayer is null!\n");
			quitGame = true;
		}
		else {
			printf("LuaPlayer x=%i, y=%i, name=%s\n", luaPlayer->x, luaPlayer->y, luaPlayer->name.c_str());
			player = new Player(new Properties("main_spritesheet", luaPlayer->x, luaPlayer->y, luaPlayer->width, luaPlayer->height, false));
			player->SetTileIndex(3802); // hardcoded for now...
		}

		luaHandler->LoadLuaMap("main_map.lua");

		luaHandler->RunTestScript("test.lua");
	}

	void GameSystem::InitSubsystems(void) {
		// Initialize main SDL modules
		InitMainSDLModule();
		InitSDLSettings();
		InitWindow();
		InitRenderer();
		InitGraphics();

		InitInputs();

		// SFXs
		InitSFX();

		// Load assets
		LoadAssets();

		// Initialize scenes
		InitScenes();

		// Start game loop
		StartGameLoop();
	}

	void GameSystem::InitMainSDLModule( void ) {
		SDL_Log( "initializing SDL" );
		if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
			SDL_LogError( SDL_LogCategory::SDL_LOG_CATEGORY_SYSTEM, "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}
	}

	void GameSystem::InitSDLSettings( void ) {
		SDL_Log( "Initializing linear texture filtering" );
		if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			SDL_LogError( SDL_LogCategory::SDL_LOG_CATEGORY_RENDER, "Warning: Linear texture filtering not enabled!" );
		}
	}

	void GameSystem::InitWindow( void ) {
		window = new Window( this->fullScreen );
		window->Init( game->windowWidth, game->windowHeight, APP_NAME.c_str() );
	}

	void GameSystem::InitRenderer( void ) {
		SDL_Log( "Initializing renderer" );
		// keep v-sync on
		renderer = SDL_CreateRenderer( 
			window->GetWindow(), 
			-1, 
			vsyncOn ? (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) : (SDL_RENDERER_ACCELERATED)
		);
		if ( renderer == NULL ) {
			SDL_LogError( SDL_LogCategory::SDL_LOG_CATEGORY_RENDER, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}

		SDL_RendererInfo rendererInfo;
		SDL_GetRendererInfo(renderer, &rendererInfo);

		SDL_Log("Renderer: %s", rendererInfo.name);

		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	}

	void GameSystem::InitGraphics( void ) {
		SDL_Log( "Initializing image subsystems" );
		int imgFlags = IMG_INIT_PNG;
		if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
			SDL_LogError( SDL_LogCategory::SDL_LOG_CATEGORY_RENDER, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			exit( 1 );
		}
	}

	void GameSystem::InitLuaHandler(void) {
		SDL_Log("Initializing Lua State");
		luaHandler = new LuaHandler();
	}

	void GameSystem::InitInputs( void ) {
		inputs = new SUD::Inputs();
		inputs->Init( window->GetWindow(), game->windowWidth / 2, game->windowHeight / 2, "mouse_cursor.png");
	}

	void GameSystem::InitSFX( void ) {
		music = new Music();
		if ( !music->Init() ) {
			printf( "Cannot initialize BASS!\n" );
			exit( 1 );
		}
	}

	void GameSystem::LoadAssets(void) {
		SDL_Log("Loading assets");

		// TEXTURES
		SDL_Log("Loading images");
		TextureManager::GetInstance()->Load("mm_gui_button", DIR_RES_IMAGES + "mm-gui-button.png");
		TextureManager::GetInstance()->Load("noto_0", DIR_RES_FONTS + "noto_0.png");
		TextureManager::GetInstance()->Load("vingue_0", DIR_RES_FONTS + "vingue_0.png");


		// FONTS
		SDL_Log("Loading fonts");
		notoFont = new Font("noto", TextureManager::GetInstance()->GetSpriteSheet("noto_0")->texture);
		vingueFont = new Font("vingue", TextureManager::GetInstance()->GetSpriteSheet("vingue_0")->texture);


		// MUSIC
		//music->LoadFile( "1fineday.xm", true ); // One fine day... https://modarchive.org/index.php?request=view_by_moduleid&query=60034
		//music->LoadFile( "menu-music.ogg", true ); // I don't know, I don't remember
		//music->LoadFile( "icefront.s3m", true ); // Ice Frontier https://modarchive.org/index.php?request=view_by_moduleid&query=44366
		//music->LoadFile( "a_world_of_dreams_5.mod", true ); // A World Of Dreams 5 https://modarchive.org/index.php?request=view_by_moduleid&query=85975
		//music->SetVolume( 0.25f );
		//music->PlayMusic();


		if (!lockedRefreshSettings) {
			SDL_Log("V - vsync ON/OFF\n");
			SDL_Log("B - FPS lock to %f ON/OFF\n", amountOfTicks);
		}

	}

	void GameSystem::InitScenes( void ) {
		scene = new Scene("loading_scene", renderer);

		// UI ELEMENTS
		mm_gui_button = new UI(new Properties("", 20, 720, 98, 32, true, "RELOAD", notoFont, COLOR_WHITE, COLOR_BLUE, COLOR_RED));

		scene->AddUIObject("mm_gui_button", mm_gui_button);
		
		if (level != nullptr && player != nullptr) {
			level->Reload(luaHandler->GetTiledMap());
			scene->SetLevel(level);
			scene->SetPlayer(player);
		}
		else {
			printf("WARNING!: level, scene and player objects must not be NULL !\n");
		}
		
		scene->Load();

		TiledMap* tiledMap = luaHandler->GetTiledMap();

		if (tiledMap != nullptr && scene != nullptr) {
			level->Reload(tiledMap);
			scene->SetLevel(level);
		}
	}

	SDL_Renderer* GameSystem::GetRenderer() {
		return renderer;
	}

	void GameSystem::Input( void ) {

		while ( SDL_PollEvent( inputs->event ) != 0 ) {
			if ( ( *inputs->event).type == SDL_QUIT ) {
				quitGame = true;
			} else {

				window->Input( inputs->event );

				if ( ( *inputs->event).type == SDL_KEYDOWN ) {
					switch ( ( *inputs->event).key.keysym.sym ) {
						case SDLK_ESCAPE:
							quitGame = true;
							break;

						default:
							break;
					}
				}

				if ( ( *inputs->event).type == SDL_KEYUP ) {
					switch ( ( *inputs->event).key.keysym.sym ) {
						case SDLK_v:
							if ( !lockedRefreshSettings ) {
								vsyncOn = !vsyncOn;
								SDL_RenderSetVSync(this->renderer, vsyncOn);
							}
							break;

						case SDLK_b:
							if (!lockedRefreshSettings) {
								fpsCap = !fpsCap;
							}
							break;

						default:
							break;
					}
				}

				inputs->ResolveInputs();

				/*if (inputs->keys[Key_Left].keyDown) {
					printf("LEFT\n");
				}*/

				scene->Input( inputs->event );
			}
		}
	}

	void GameSystem::Update( double dt ) {
		window->Update( dt );
		if (reloadLuaScripts) {
			reloadLuaScripts = false;
			LoadLuaScripts();
		}
		scene->Update( dt );
		if ( mm_gui_button->isClicked ) {
			reloadLuaScripts = true;
			mm_gui_button->isClicked = false;
		}
	}

	void GameSystem::Render( void ) {
		if (!reloadLuaScripts) {
			scene->Draw();
		}	
		
		std::stringstream ssFps;
		ssFps << "FPS: " << fps_count;
		std::string sFPS = ssFps.str();
		std::wstring levelDetails = strconverter.from_bytes(sFPS);

		std::stringstream ssVsync;
		ssVsync << "VSYNC: " << (vsyncOn ? "ON" : "OFF");
		std::string sVsync = ssVsync.str();
		std::wstring vSync = strconverter.from_bytes(sVsync);

		std::stringstream ssFpsCap;
		ssFpsCap << "FPS CAP: " << (fpsCap ? "ON" : "OFF");
		std::string sFpsCap = ssFpsCap.str();
		std::wstring vFpsLock = strconverter.from_bytes(sFpsCap);

		notoFont->Draw( levelDetails, 10, 10, 14.0f, COLOR_YELLOW );
		notoFont->Draw( vSync, 10, 40, 14.0f, COLOR_YELLOW);
		notoFont->Draw( vFpsLock, 10, 70, 14.0f, COLOR_CYAN );

		//notoFont->Draw( L"A¥BCÆDEÊFGHIJKL£MNÑOÓPRSŒTUWYZ¯", 10, 10, 10.0f, COLOR_CYAN );
		//notoFont->Draw( L"A¥B CÆD EÊF GHI JKL £MN ÑOÓ PRS ŒTU WYZ ¯", 10, 50, 10.0f, COLOR_CYAN );
		//notoFont->Draw( L"a¹bcædeêfghijkl³mnñoóprsœtuwyz¿Ÿ", 10, 90, 10.0f, COLOR_YELLOW );
		//notoFont->Draw( L"1234567890-=!@#$%^&*()_+{}:;',\"./?<>", 10, 130, 10.0f, COLOR_GREEN );

		//notoFont->Draw( levelDetails, 10, 30, 16.0f, COLOR_YELLOW);

		//notoFont->Draw( L"A¥CÆEÊL£NÑOÓSŒZ¯a¹cæeêl³nñoósœzŸ¿", 10, 100, 2.0f, COLOR_GREEN );
		//vingueFont->Draw( L"A¥CÆEÊL£NÑOÓSŒZ¯a¹cæeêl³nñoósœzŸ¿", 10, 50, 32.0f );

		//notoFont->Draw( L"Pewnego razu trzy œwinki posz³y na spacer w góry.", 10, 220, 2.0f, COLOR_CYAN );
		//notoFont->Draw( L"By³a przepiêkna pogoda.", 10, 260, 16.0f, COLOR_YELLOW );
		//notoFont->Draw( L"Trzy œwinki zgubi³y siê w górach...", 10, 300, 16.0f, COLOR_GRAY );
	}

	void GameSystem::StartGameLoop( void ) {
		lastTime = SDL_GetTicks();
		timer = SDL_GetTicks();

		while ( !quitGame ) {
			ns = 1000.0f / amountOfTicks;
			now = SDL_GetTicks();
			delta += (now - lastTime) / ns;
			lastTime = now;

			while (delta >= 1.0f) {
				Input();

				if (window->windowFocusGain) {
					printf("Window focus gain\n");
				}

				if (window->windowFocusLost) {
					printf("Window focus lost\n");
				}

				Update(delta);

				// Update screen
				if (fpsCap) {
					SDL_RenderPresent(renderer);
					SDL_RenderClear(renderer);
					Render();
					frames++;
				}

				updates++;
				delta--;
			}

			if (!fpsCap) {
				SDL_RenderPresent(renderer);
				SDL_RenderClear(renderer);
				Render();
				frames++;
			}

			if (SDL_GetTicks() - timer > 1000) {
				timer += 1000;
				fps_count = frames;
				ticks_count = updates;
				frames = 0;
				updates = 0;
				//printf("FPS: %i, TICKS: %i, delta: %f\n", fps_count, ticks_count, delta);
			}

			if (fpsCap) {
				SDL_Delay(1);
			
		} // end while loop
		Exit();
	}

}
