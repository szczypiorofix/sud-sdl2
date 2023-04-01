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
		level = new Level();

		vsyncOn = false;
		lockFPS = false;
		fullScreen = false;

		lockedRefreshSettings = false;

		quitGame = false;


		lastTime = 0L;
		delta = 0.0f;
		timer = 0L;
		updates = 0;
		frames = 0;
		now = 0L;
		amountOfTicks = 40.0f;
		fps_count = 0;
		ticks_count = 0;
		ns = 0.0f;
		fpsCap = false;

		levelDetails = L"";

		reloadLuaScripts = false;

		// Run only Lua scripts, without SDL window
		runLuaScriptsOnly = false;
	}


	void GameSystem::CloseWindow( void ) {
		luaHandler->Close();

		scene->Unload();

		delete notoFont;
		delete vingueFont;

		delete music;

		delete mm_gui_button;

		delete level;

		TextureManager::GetInstance()->Clean();

		SDL_DestroyRenderer( renderer );
		renderer = NULL;

		window->Destroy();

		IMG_Quit();
		SDL_Quit();
	}


	void GameSystem::InitSubsystems() {
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


	void GameSystem::Start( int argc, char* args[] ) {

		if ( argc > 1 ) {
			SDL_Log("Game app arguments count: %i\n", argc);
			SDL_Log( "Args[0]: %s\n", args[0]);
		}

		// Initialize Lua scripts handler
		InitLuaHandler();

		LoadLuaScripts();

		if ( runLuaScriptsOnly ) {
			luaHandler->Close();
			exit(0);
		}

		InitSubsystems();
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
		//TextureManager::GetInstance()->Load("main_spritesheet", DIR_RES_IMAGES + "spritesheet.png", 32, 32);
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
			SDL_Log("F1 - vsync ON/OFF\n");
			SDL_Log("F2 - FPS lock to %f ON/OFF\n", amountOfTicks);
		}

	}


	void GameSystem::InitScenes( void ) {
		
		scene = new Scene("loading_scene", renderer);

		// UI ELEMENTS
		mm_gui_button = new UI(new Properties("", 20, 720, 98, 32, true, "RELOAD", notoFont, COLOR_WHITE, COLOR_BLUE, COLOR_RED));

		scene->AddUIObject("mm_gui_button", mm_gui_button);
		scene->Load();


		/*std::stringstream ss;
		ss << "Game level: " << "width=" << levelMap->width << ", height=" << levelMap->height;
		std::string ld = ss.str();
		levelDetails = strconverter.from_bytes(ld);*/

		TiledMap* tiledMap = luaHandler->GetTiledMap();

		if (tiledMap != nullptr && scene != nullptr) {
			level->Reload(tiledMap);
			scene->SetLevel(level);
		}

	}

	SDL_Renderer* GameSystem::GetRenderer() {
		return renderer;
	}

	void GameSystem::LoadLuaScripts() {
		// LUA SCRIPT

		luaHandler->Close();

		// ===============================================================================
		// 
		// IDEAS:
		// - run lua scripts before initializing of SDL
		// - create SLD window calling lua functions
		// - initialize all game functions using Lua scripts? Look soooo coooool! iksde
		// 
		// ===============================================================================

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
		
		if (renderer != nullptr) {
			SDL_RenderSetVSync(renderer, this->vsyncOn);
		}
		

		//printf("GameSystem: game object, name=%s, game->level name=%s\n", game->name.c_str(), game->level->name.c_str() );
		/*printf("GameSystem: level object, name=%s, width=%i, height=%i\n", level->name.c_str(), level->width, level->height);*/
		//if ( game != nullptr && game->level != nullptr ) {
		//	std::stringstream ss;
		//	ss << "Game level: name=" << game->level->name << ", width=" << game->level->width << ", height=" << game->level->height;
		//	std::string ld = ss.str();
		//	levelDetails = strconverter.from_bytes(ld);
		//	//std::cout << ld.c_str() << std::endl;
		//	//scene->SetLevel(game->level);
		//}


		luaHandler->LoadLuaMap("main_map.lua");
		
		if (level != nullptr && scene != nullptr) {
			level->Reload(luaHandler->GetTiledMap());
			scene->SetLevel(level);
		}

		luaHandler->RunTestScript("test.lua");
	}


	void GameSystem::Input( void ) {

		while ( SDL_PollEvent( inputs->event ) != 0 ) {
			if ( ( *inputs->event).type == SDL_QUIT ) {
				quitGame = true;
			} else {

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
						case SDLK_F1:
							if ( !lockedRefreshSettings ) {
								vsyncOn = !vsyncOn;
								SDL_RenderSetVSync(this->renderer, vsyncOn);
							}
							break;

						case SDLK_F2:
							if (!lockedRefreshSettings) {
								lockFPS = !lockFPS;
							}
							break;

						case SDLK_F5:
							//SDL_RenderSetVSync(this->renderer, 1);
							break;

						default:
							break;
					}
				}

				if ((*inputs->event).type == SDL_WINDOWEVENT ) {
					switch ((*inputs->event).window.event) {
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						//printf("Focus gain\n");
						inputs->windowFocusGain = true;
						break;

					case SDL_WINDOWEVENT_FOCUS_LOST:
						//printf("Focus lost\n");
						inputs->windowFocusLost = true;
						break;

					default:
						break;
					}
				}

				inputs->ResolveInputs();

				if (inputs->keys[Key_Left].keyDown) {
					printf("LEFT\n");
				}

				scene->Input( inputs->event);
			}
		}
	}

	void GameSystem::Update( double dt ) {
		if (reloadLuaScripts) {
			reloadLuaScripts = false;
			LoadLuaScripts();
		}
		scene->Update( dt );
		if ( mm_gui_button->isClicked ) {
			reloadLuaScripts = true;
			mm_gui_button->isClicked = false;
		}

		inputs->windowFocusGain = false;
		inputs->windowFocusLost = false;

	}

	void GameSystem::Render( void ) {
		
		if (!reloadLuaScripts) {
			scene->Draw();
		}
		

		//font->Draw( "•C∆ £—”åSØèπÊÍ≥ÒÛúøü FPS: " + std::to_string( fps ), 10, 10, 0.60f);
		std::wstring vs = vsyncOn ? L"ON" : L"OFF";
		//std::wstring fpslk = lockFPS ? L"ON" : L"OFF";
		
		std::stringstream ss;
		ss << "FPS: " << fps_count;
		std::string ld = ss.str();
		levelDetails = strconverter.from_bytes(ld);
		//	//std::cout << ld.c_str() << std::endl;
		//std::wstring fpsStr = L"FPS:" << L"s";

		notoFont->Draw(levelDetails, 10, 10, 14.0f, COLOR_YELLOW );
		notoFont->Draw( L"VSYNC: " + vs, 10, 40, 14.0f, COLOR_YELLOW);
		//notoFont->Draw( L"FPS LOCK (60): " + fpslk, 10, 70, 14.0f, COLOR_CYAN );

		//notoFont->Draw( L"A•BC∆DE FGHIJKL£MN—O”PRSåTUWYZØè", 10, 10, 10.0f, COLOR_CYAN );
		//notoFont->Draw( L"A•B C∆D E F GHI JKL £MN —O” PRS åTU WYZ Øè", 10, 50, 10.0f, COLOR_CYAN );
		//notoFont->Draw( L"aπbcÊdeÍfghijkl≥mnÒoÛprsútuwyzøü", 10, 90, 10.0f, COLOR_YELLOW );
		//notoFont->Draw( L"1234567890-=!@#$%^&*()_+{}:;',\"./?<>", 10, 130, 10.0f, COLOR_GREEN );

		//notoFont->Draw( levelDetails, 10, 30, 16.0f, COLOR_YELLOW);

		//notoFont->Draw( L"A•C∆E L£N—O”SåZØèaπcÊeÍl≥nÒoÛsúzüø", 10, 100, 2.0f, COLOR_GREEN );
		//vingueFont->Draw( L"A•C∆E L£N—O”SåZØèaπcÊeÍl≥nÒoÛsúzüø", 10, 50, 32.0f );

		//notoFont->Draw( L"Pewnego razu trzy úwinki posz≥y na spacer w gÛry.", 10, 220, 2.0f, COLOR_CYAN );
		//notoFont->Draw( L"By≥a przepiÍkna pogoda.", 10, 260, 16.0f, COLOR_YELLOW );
		//notoFont->Draw( L"Trzy úwinki zgubi≥y siÍ w gÛrach...", 10, 300, 16.0f, COLOR_GRAY );

	}

	void GameSystem::StartGameLoop( void ) {
		
		lastTime = SDL_GetTicks();
		timer = SDL_GetTicks();

		while ( !quitGame ) {

			ns = 1000.0f / amountOfTicks;
			now = SDL_GetTicks();
			delta += (now - lastTime) / ns;
			lastTime = now;

			while (delta >= 1) {
				Input();

				if (inputs->windowFocusGain) {
					printf("Window focus gain\n");
				}

				if (inputs->windowFocusLost) {
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
				printf("FPS: %i, TICKS: %i, delta: %f\n", fps_count, ticks_count, delta);
			}

			if (fpsCap) {
				SDL_Delay(1);
			}

		} // end while loop

		CloseWindow();
	}

}
