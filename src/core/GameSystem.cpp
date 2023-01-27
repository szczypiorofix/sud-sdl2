#include "GameSystem.h"


namespace SUD {

	GameSystem::GameSystem( void ) {
		window = NULL;
		renderer = NULL;
		inputs = new SUD::Inputs();

		cursor = NULL;

		fontTexture = NULL;
		font = NULL;

		scene = NULL;

		luaHandler = NULL;
		
		quitGame = false;

		delta = 0.0001f;
		time2 = 0.0f;
		start = 0;
		end = 0;
		secondsElapsed = 0.0f;
	}


	void GameSystem::Close( void ) {
		scene->Unload();

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
		renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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
			printf("Cannot initialize mouse cursor surface!\m");
			exit( 1 );
		}
		cursor = SDL_CreateColorCursor( cursorIcon, 0, 0 );
		if ( cursor == nullptr ) {
			printf( "Cannot attach mouse icon to cursor!\m" );
			exit( 1 );
		}
		SDL_SetCursor( cursor );
	}


	void GameSystem::InitScenes(void) {
		scene = new Scene("loading_scene", renderer);
	}


	void GameSystem::LoadAssets( void ) {

		SDL_Log( "Loading assets" );

		TextureManager::GetInstance()->Load( "mm_gui_button", DIR_RES_IMAGES + "mm-gui-button.png" );
		TextureManager::GetInstance()->Load( "main_spritesheet", DIR_RES_IMAGES + "spritesheet.png");

		SDL_Log("Loading font");
		fontTexture = new Texture( DIR_RES_FONTS + "vingue.png", renderer );
		font = new Font( "vingue", fontTexture );

		UI* mm_gui_button = new UI(new Properties("mm_gui_button", 360, 300, 168, 32));

		//printf("UI name %s\n", logo->GetProps()->TextureID.c_str() );
		//printf( "UI width %d\n", logo->GetProps()->Width );
		

		scene->AddUIObject( "mm_gui_button", mm_gui_button );

		//Vector2D v1(1, 2), v2(3,4), v3(0,0);
		//v3 = v1 * 2;
		//v3.Log("v3: ");


		//Transform tf;
		//tf.Log();



		if (luaHandler->LoadFile("script1.lua")) {
			printf("Successfully loaded lua script!\n");

			int xx = 0;
			luaHandler->GetInt("x", xx);
			printf("Lua script: x = %d\n", xx);

			int valueFromFunction = 0;
			luaHandler->GetFunctionIntValue( "GetSomeValue", valueFromFunction );
			printf("Get value from Lua function? : %d\n", valueFromFunction );

			std::vector<std::string> returnValues{};
			luaHandler->GetFunctionStringTuple( "DawajMnieTupla", returnValues, 2 );
			for ( unsigned int i = 0; i < returnValues.size(); i++ ) {
				printf("DawajMnieTupla value %d = %s\n", i, returnValues.at(i).c_str());
			}

			luaHandler->Close();
		}



		//if (luaHandler->ProcessText("x=476")) {
		//	int xx = 0;
		//	luaHandler->GetInt("x", xx);
		//	printf("Lua script: xx = %d\n", xx);
		//	luaHandler->Close();
		//}
		//else {
		//	printf("Cannot process Lua script as string!\n");
		//}



		scene->Load();

	}

	SDL_Renderer* GameSystem::GetRenderer() {
		return renderer;
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
		printf("Seconds: %.2f\n", secondsElapsed);
	}

	void GameSystem::Render( void ) {

		scene->Draw();

		//font->Draw(std::string( "FPS: " + std::to_string( secondsElapsed ) ).c_str(), 10, 10, 0.25f );

		//font->draw( "single user DUNGEON", 50, 50, 0.35f );
		//TextureManager::GetInstance()->Draw( "main_spritesheet", 10, 10, 128, 128, SDL_FLIP_NONE );

	}

	void GameSystem::GameLoop( void ) {
		
		time2 = SDL_GetTicks();

		while ( !quitGame ) {
		
			delta = ( SDL_GetTicks() - time2 ) / 1000;
			time2 = SDL_GetTicks();
			
			start = SDL_GetPerformanceCounter();

			Input();
			Update( delta );

			// Clear renderer
			SDL_RenderClear( renderer );

			// draw everything
			Render();

			// Update screen
			SDL_RenderPresent( renderer );

			end = SDL_GetPerformanceCounter();
			secondsElapsed = ( end - start ) / ( float ) SDL_GetPerformanceFrequency() * 1000.0f;


			SDL_Delay( 16.66666f - secondsElapsed );

		}

		Close();
	}

}
