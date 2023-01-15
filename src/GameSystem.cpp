#include "GameSystem.h"


namespace SUD {


	GameSystem::GameSystem() {
		this->window = NULL;
		this->renderer = NULL;
	}

	GameSystem::~GameSystem() {
		printf( "Destring GameSystem..." );
	}


	void GameSystem::close() {

		SDL_DestroyRenderer( this->renderer );
		SDL_DestroyWindow( this->window );
		this->window = NULL;
		this->renderer = NULL;

		IMG_Quit();
		SDL_Quit();

	}

	void GameSystem::launch() {
		this->initMainSDLModule();
		this->initSDLSettings();
		this->initWindow();
		this->initRenderer();
		this->initGraphics();

		this->gameLoop();
	}




	void GameSystem::initMainSDLModule() {
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}
	}

	void GameSystem::initSDLSettings() {
		//Set texture filtering to linear
		if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
	}

	void GameSystem::initWindow() {
		this->window = SDL_CreateWindow( "Single User Dungeon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if ( this->window == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}
	}

	void GameSystem::initRenderer() {
		this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );
		if ( this->renderer == NULL ) {
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}

		SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );

	}

	void GameSystem::initGraphics() {
		int imgFlags = IMG_INIT_PNG;
		if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			exit( 1 );
		}

	}
	

	void GameSystem::gameLoop() {

		bool quit = false;

		while ( !quit ) {

			while ( SDL_PollEvent( &eventHandler ) != 0 ) {

				if ( eventHandler.type == SDL_QUIT ) {
					quit = true;
				} else {
					if ( eventHandler.type == SDL_KEYDOWN ) {

						switch ( eventHandler.key.keysym.sym ) {

							case SDLK_ESCAPE:
								quit = true;
								break;

							default:
								break;

						}

					}
				}
			}



			SDL_RenderClear( this->renderer );

			//Render texture to screen
			//SDL_RenderCopy( this->renderer, gTexture, NULL, NULL );

			//Update screen
			SDL_RenderPresent( this->renderer );
		}

		this->close();

	}

}


