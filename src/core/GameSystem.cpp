#include "GameSystem.h"
#include <codecvt>
#include <locale>
#include <sstream>


using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;


namespace SUD {

	GameSystem::GameSystem( void ) {
		window = nullptr;
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
		

		vsyncOn = true;
		lockFPS = false;

		lockedRefreshSettings = true;

		quitGame = false;

		// timers
		startPerf = 0;
		endPerf = 0;
		elapsedMS = 0.0f;
		targetFPS = 60.0f;
		startTicks = 0;
		frameTime = 0.0f;
		endTicks = 0;
		_fps = 0.0f;
		delayMS = 0.0f;
		delayMSCounter = 0;
		delayFrameCounter = 0;
		fpsSum = 0.0f;
		FPS = 0;

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

		TextureManager::GetInstance()->Clean();

		SDL_DestroyRenderer( renderer );
		renderer = NULL;

		window->Destroy();

		IMG_Quit();
		SDL_Quit();
	}


	void GameSystem::InitGame() {

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
		GameLoop();

	}


	void GameSystem::Launch( int argc, char* args[] ) {

		if ( argc > 1 ) {
			SDL_Log("Game app arguments count: %i\n", argc);
			SDL_Log( "Args[0]: %s\n", args[0]);
		}

		// Initialize Lua scripts handler
		InitLuaHandler();

		ReloadLuaScripts();

		InitGame();
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
		window = new Window();
		window->Init( game->windowWidth, game->windowHeight, APP_NAME.c_str() );
	}

	void GameSystem::InitRenderer( void ) {
		SDL_Log( "Initializing renderer" );
		// keep v-sync on
		renderer = SDL_CreateRenderer( window->GetWindow(), -1, vsyncOn ? (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) : (SDL_RENDERER_ACCELERATED));
		if ( renderer == NULL ) {
			SDL_LogError( SDL_LogCategory::SDL_LOG_CATEGORY_RENDER, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}

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
		luaHandler = new LUA::LuaHandler();
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
		TextureManager::GetInstance()->Load("main_spritesheet", DIR_RES_IMAGES + "spritesheet.png");
		TextureManager::GetInstance()->Load("noto_0", DIR_RES_FONTS + "noto_0.png");
		TextureManager::GetInstance()->Load("vingue_0", DIR_RES_FONTS + "vingue_0.png");

		// FONTS
		SDL_Log("Loading fonts");
		notoFont = new Font("noto", TextureManager::GetInstance()->GetTexture("noto_0"));
		vingueFont = new Font("vingue", TextureManager::GetInstance()->GetTexture("vingue_0"));





		// MUSIC
		//music->LoadFile( "1fineday.xm", true ); // One fine day... https://modarchive.org/index.php?request=view_by_moduleid&query=60034
		//music->LoadFile( "menu-music.ogg", true ); // I don't know, I don't remember
		//music->LoadFile( "icefront.s3m", true ); // Ice Frontier https://modarchive.org/index.php?request=view_by_moduleid&query=44366
		//music->LoadFile( "a_world_of_dreams_5.mod", true ); // A World Of Dreams 5 https://modarchive.org/index.php?request=view_by_moduleid&query=85975
		//music->SetVolume( 0.25f );
		//music->PlayMusic();

		if (!lockedRefreshSettings) {
			printf("F1 - vsync ON/OFF\n");
			printf("F2 - FPS lock to %f ON/OFF\n", targetFPS);
		}

	}


	void GameSystem::InitScenes( void ) {
		scene = new Scene("loading_scene", renderer);

		// UI ELEMENTS
		mm_gui_button = new UI(new Properties("", 20, 720, 98, 32, true, "RELOAD", notoFont, COLOR_WHITE, COLOR_BLUE, COLOR_RED));

		scene->AddUIObject("mm_gui_button", mm_gui_button);

		scene->Load();

		scene->SetLevel(game->level);

		//reloadLuaScripts = true;

	}

	SDL_Renderer* GameSystem::GetRenderer() {
		return renderer;
	}

	void GameSystem::ReloadLuaScripts() {
		// LUA SCRIPT

		//CloseWindow();

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
			game = new LUA::Object::Game("default_game");
		}

		//printf("GameSystem: game object, name=%s, game->level name=%s\n", game->name.c_str(), game->level->name.c_str() );
		/*printf("GameSystem: level object, name=%s, width=%i, height=%i\n", level->name.c_str(), level->width, level->height);*/


		if ( game != nullptr && game->level != nullptr ) {
			std::stringstream ss;
			ss << "Game level: name=" << game->level->name << ", width=" << game->level->width << ", height=" << game->level->height;
			std::string ld = ss.str();
			levelDetails = strconverter.from_bytes(ld);

			//std::cout << ld.c_str() << std::endl;

			//scene->SetLevel(game->level);
		}


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
							}
							break;

						case SDLK_F2:
							if (!lockedRefreshSettings) {
								lockFPS = !lockFPS;
							}
							break;

						default:
							break;
					}
				}
				scene->Input( inputs->event);
			}
		}
	}

	void GameSystem::Update( double dt ) {
		
		scene->Update( dt );

		if ( mm_gui_button->isClicked ) {
			reloadLuaScripts = true;
		}

		if ( reloadLuaScripts ) {
			reloadLuaScripts = false;
			//system( "cls" );
			ReloadLuaScripts();
		}

	}

	void GameSystem::Render( void ) {
		scene->Draw();

		//font->Draw( "¥CÆÊ£ÑÓŒS¯¹æê³ñóœ¿Ÿ FPS: " + std::to_string( fps ), 10, 10, 0.60f);
		
		//std::wstring vs = vsyncOn ? L"ON" : L"OFF";
		//std::wstring fpslk = lockFPS ? L"ON" : L"OFF";

		//notoFont->Draw( L"AVG FPS ssss 1234567890", 10, 10, 14.0f, COLOR_RED );
		//notoFont->Draw( L"VSYNC: " + vs, 10, 40, 14.0f, COLOR_CYAN);
		//notoFont->Draw( L"FPS LOCK (60): " + fpslk, 10, 70, 14.0f, COLOR_CYAN );

		//notoFont->Draw( L"A¥BCÆDEÊFGHIJKL£MNÑOÓPRSŒTUWYZ¯", 10, 10, 10.0f, COLOR_CYAN );
		//notoFont->Draw( L"A¥B CÆD EÊF GHI JKL £MN ÑOÓ PRS ŒTU WYZ ¯", 10, 50, 10.0f, COLOR_CYAN );
		//notoFont->Draw( L"a¹bcædeêfghijkl³mnñoóprsœtuwyz¿Ÿ", 10, 90, 10.0f, COLOR_YELLOW );
		//notoFont->Draw( L"1234567890-=!@#$%^&*()_+{}:;',\"./?<>", 10, 130, 10.0f, COLOR_GREEN );


		notoFont->Draw( levelDetails, 10, 30, 16.0f, COLOR_YELLOW);


		//notoFont->Draw( L"A¥CÆEÊL£NÑOÓSŒZ¯a¹cæeêl³nñoósœzŸ¿", 10, 100, 2.0f, COLOR_GREEN );
		//vingueFont->Draw( L"A¥CÆEÊL£NÑOÓSŒZ¯a¹cæeêl³nñoósœzŸ¿", 10, 50, 32.0f );


		//notoFont->Draw( L"Pewnego razu trzy œwinki posz³y na spacer w góry.", 10, 220, 2.0f, COLOR_CYAN );
		//notoFont->Draw( L"By³a przepiêkna pogoda.", 10, 260, 16.0f, COLOR_YELLOW );
		//notoFont->Draw( L"Trzy œwinki zgubi³y siê w górach...", 10, 300, 16.0f, COLOR_GRAY );

		//TextureManager::GetInstance()->Draw( "main_spritesheet", 10, 10, 256, 256, SDL_FLIP_NONE );

	}

	void GameSystem::GameLoop( void ) {
		
		while ( !quitGame ) {

			startTicks = SDL_GetTicks();
			startPerf = SDL_GetPerformanceCounter();


			Input();

			Update( 0 );

			// Clear renderer
			SDL_RenderClear( renderer );

			// draw everything
			Render();
						

			// Update screen
			SDL_RenderPresent( renderer );

			// End frame timing
			endPerf = SDL_GetPerformanceCounter();

			elapsedMS = ( endPerf - startPerf ) / ( float ) SDL_GetPerformanceFrequency() * 1000.0f;
			if ( lockFPS ) {
				delayMS = floor( ( 1000.0f / targetFPS ) - elapsedMS );
				SDL_Delay( (int)delayMS );
			}

			endTicks = SDL_GetTicks();
			frameTime = ( endTicks - startTicks ) / 1000.0f;
			_fps = 1.0f / frameTime;

			fpsSum += _fps;
			delayFrameCounter++;

			delayMSCounter += (endTicks - startTicks);

			if ( delayMSCounter >= 100 ) {
				FPS = ( int ) ( fpsSum / delayFrameCounter );
				//printf("FPS: %i\n", FPS);
				delayMSCounter = 0;
				delayFrameCounter = 0;
				fpsSum = 0.0f;
			}

		}

		CloseWindow();
	}

}
