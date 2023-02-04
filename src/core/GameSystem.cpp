#include "GameSystem.h"
#include <conio.h>
#include <iostream>

using namespace Events;


namespace SUD {

	GameSystem::GameSystem( void ) {
		window = nullptr;
		renderer = nullptr;
		inputs = new SUD::Inputs();

		cursor = nullptr;

		fontTexture = nullptr;
		font = nullptr;

		music = nullptr;

		scene = nullptr;

		luaHandler = nullptr;
		
		mm_gui_button = nullptr;

		vsyncOn = false;
		lockFPS = false;

		quitGame = false;

		// timers
		startPerf = 0;
		endPerf = 0;
		elapsedMS = 0.0f;
		targetFPS = 60.0f;
		startTicks = 0;
		frameTime = 0.0f;
		endTicks = 0;
		fps = 0.0f;

		reloadLuaScripts = 0;
	}


	void GameSystem::Close( void ) {
		scene->Unload();

		delete font;

		delete music;

		TextureManager::GetInstance()->Clean();

		SDL_DestroyRenderer( renderer );
		SDL_DestroyWindow( window );

		window = NULL;
		renderer = NULL;

		IMG_Quit();
		SDL_Quit();
	}

	void GameSystem::Launch( int argc, char* args[] ) {

		if ( argc > 1 ) {
			SDL_Log("Game app arguments count: %i\n", argc);
			SDL_Log( "Args[0]: %s\n", args[0]);
		}

		InitMainSDLModule();
		InitSDLSettings();
		InitWindow();
		InitRenderer();
		InitGraphics();

		InitLuaState();

		InitMouse();

		InitSFX();

		InitScenes();

		LoadAssets();

		GameLoop();
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
		SDL_Log( "Initializing window" );
		window = SDL_CreateWindow( APP_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if ( window == NULL ) {
			SDL_LogError( SDL_LogCategory::SDL_LOG_CATEGORY_SYSTEM, "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}
	}

	void GameSystem::InitRenderer( void ) {
		SDL_Log( "Initializing renderer" );
		// keep v-sync on
		renderer = SDL_CreateRenderer( window, -1, vsyncOn ? ( SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ) : ( SDL_RENDERER_ACCELERATED ) );
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

	void GameSystem::InitLuaState(void) {
		SDL_Log("Initializing Lua State");
		luaHandler = new LuaHandler();
	}

	void GameSystem::InitMouse( void ) {
		SDL_Log( "Initializing mouse cursor" );

		SDL_ShowCursor( SDL_ENABLE );
		SDL_WarpMouseInWindow( window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );

		SDL_Surface* cursorIcon = IMG_Load( std::string( DIR_RES_IMAGES + "mouse_cursor.png" ).c_str() );
		if ( cursorIcon == nullptr ) {
			printf("Cannot initialize mouse cursor surface!\n");
			exit( 1 );
		}
		cursor = SDL_CreateColorCursor( cursorIcon, 0, 0 );
		if ( cursor == nullptr ) {
			printf( "Cannot attach mouse icon to cursor!\n" );
			exit( 1 );
		}
		SDL_SetCursor( cursor );
	}


	void GameSystem::InitSFX( void ) {
		music = new Music();
		if ( !music->Init() ) {
			printf( "Cannot initialize BASS!\n" );
			exit( 1 );
		}
	}


	void GameSystem::InitScenes( void ) {
		scene = new Scene("loading_scene", renderer);
	}


	//void clickCallback() {
	//	printf("Click callback!\n");
	//}


	void GameSystem::LoadAssets( void ) {
		SDL_Log( "Loading assets" );

		// TEXTURES
		TextureManager::GetInstance()->Load( "mm_gui_button", DIR_RES_IMAGES + "mm-gui-button.png" );
		TextureManager::GetInstance()->Load( "main_spritesheet", DIR_RES_IMAGES + "spritesheet.png");

		// FONTS
		SDL_Log("Loading font");
		fontTexture = new Texture( DIR_RES_FONTS + "noto_0.png", renderer );
		font = new Font( "noto", fontTexture );

		// UI ELEMENTS
		mm_gui_button = new UI(new Properties("mm_gui_button", 360, 300, 168, 32));
		//mm_gui_button->AddOnClickCallback( clickCallback );


		//UIEvent e = { 12, "Todd" };
		//UIEvents* evt = new UIEvents( e );

		//mm_gui_button->AddOnClickCallback( evt, &UIEvents::OnClickCallback );

		scene->AddUIObject( "mm_gui_button", mm_gui_button );


		// LUA SCRIPTS
		ReloadLuaScripts();


		// SCENE
		scene->Load();

		// MUSIC
		//music->LoadFile( "1fineday.xm", true ); // One fine day... https://modarchive.org/index.php?request=view_by_moduleid&query=60034
		//music->LoadFile( "menu-music.ogg", true ); // I don't know, I don't remember
		//music->LoadFile( "icefront.s3m", true ); // Ice Frontier https://modarchive.org/index.php?request=view_by_moduleid&query=44366
		music->LoadFile( "a_world_of_dreams_5.mod", true ); // A World Of Dreams 5 https://modarchive.org/index.php?request=view_by_moduleid&query=85975
		music->SetVolume( 0.25f );
		music->PlayMusic();

	}

	SDL_Renderer* GameSystem::GetRenderer() {
		return renderer;
	}

	void GameSystem::ReloadLuaScripts() {
		// LUA SCRIPTS
		luaHandler->LoadFile( "script1.lua" );
		luaHandler->Close();
	}


	void GameSystem::Input( void ) {
		while ( SDL_PollEvent( inputs->eventHandler ) != 0 ) {
			if ( ( *inputs->eventHandler ).type == SDL_QUIT ) {
				quitGame = true;
			} else {
				if ( ( *inputs->eventHandler ).type == SDL_KEYDOWN ) {
					switch ( ( *inputs->eventHandler ).key.keysym.sym ) {
						case SDLK_ESCAPE:
							quitGame = true;
							break;
						default:
							break;
					}
				}

				scene->Input( inputs->eventHandler );
			}
		}
	}

	void GameSystem::Update( double dt ) {
		
		scene->Update( dt );

		if ( mm_gui_button->isClicked ) {
			printf( "GameSystem - button was clicked!\n" );
			if ( reloadLuaScripts == 0 ) {
				reloadLuaScripts = 1;
			}
		}

		if ( reloadLuaScripts == 1 ) {
			reloadLuaScripts = 0;
			system( "cls" );
			ReloadLuaScripts();
		}

	}

	void GameSystem::Render( void ) {
		scene->Draw();


		//font->Draw( "¥CÆÊ£ÑÓŒS¯¹æê³ñóœ¿Ÿ FPS: " + std::to_string( fps ), 10, 10, 0.60f);
		//font->Draw( L"A¥CÆEÊL£NÑOÓSŒZ¯a¹cæeêl³nñoósœzŸæ", 10, 10, 0.60f );
		


		font->Draw( L"Pewnego razu trzy œwinki posz³y na spacer w góry.", 10, 20, 0.60f );
		font->Draw( L"By³a przepiêkna pogoda.", 10, 60, 0.60f );



		//printf("¥ÆÊ£ÑÓŒ¯¹æê³ñóœ¿Ÿ FPS \n");
		//font->Draw( "single user DUNGEON", 50, 50, 0.35f );
		//TextureManager::GetInstance()->Draw( "main_spritesheet", 10, 10, 128, 128, SDL_FLIP_NONE );
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
				SDL_Delay( floor( ( 1000.0f / targetFPS ) - elapsedMS ) );
			}

			endTicks = SDL_GetTicks();
			frameTime = ( endTicks - startTicks ) / 1000.0f;
			fps = 1.0f / frameTime;

		}

		Close();
	}

}
