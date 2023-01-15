#include "GameSystem.h"


namespace SUD {

	GameSystem::GameSystem() {
		this->window = NULL;
		this->renderer = NULL;
		this->inputs = new Inputs();
		
		this->backgoundTexture = NULL;

		this->quitGame = false;
	}

	GameSystem::~GameSystem() {
		printf( "Destring GameSystem..." );
	}

	void GameSystem::close() {

		SDL_DestroyRenderer( this->renderer );
		SDL_DestroyWindow( this->window );
		this->window = NULL;
		this->renderer = NULL;

		this->quitGame = false;

		IMG_Quit();
		SDL_Quit();

	}

	void GameSystem::launch() {
		this->initMainSDLModule();
		this->initSDLSettings();
		this->initWindow();
		this->initRenderer();
		this->initGraphics();

		this->loadAssets();

		this->gameLoop();
	}

	void GameSystem::initMainSDLModule() {
		printf( "SYSTEM: initializing SDL - " );
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}
		this->printOK();
	}

	void GameSystem::initSDLSettings() {
		printf( "SYSTEM: Initializing linear texture filtering - " );
		if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		this->printOK();
	}

	void GameSystem::initWindow() {
		printf( "SYSTEM: Initializing window - " );
		this->window = SDL_CreateWindow( APP_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if ( this->window == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}
		this->printOK();
	}

	void GameSystem::initRenderer() {
		printf( "SYSTEM: Initializing renderer - " );
		this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );
		if ( this->renderer == NULL ) {
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}

		SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );
		this->printOK();
	}

	void GameSystem::initGraphics() {
		printf( "SYSTEM: Initializing images subsystems - " );
		int imgFlags = IMG_INIT_PNG;
		if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			exit( 1 );
		}
		this->printOK();
	}

	void GameSystem::loadAssets() {
		printf( "SYSTEM: loading assets - " );
		
		this->backgoundTexture = new Texture("res/spritesheet.png", this->renderer);
		
		this->printOK();
	}

	void GameSystem::input() {
		while ( SDL_PollEvent( this->inputs->eventHandler ) != 0 ) {
			if ( ( *this->inputs->eventHandler ).type == SDL_QUIT ) {
				this->quitGame = true;
			} else {
				if ( ( *this->inputs->eventHandler ).type == SDL_KEYDOWN ) {
					switch ( ( *this->inputs->eventHandler ).key.keysym.sym ) {
						case SDLK_ESCAPE:
							this->quitGame = true;
							break;
						default:
							break;
					}
				}
			}
		}
	}

	void GameSystem::update() {

	}

	void GameSystem::render() {
		this->backgoundTexture->draw();
	}

	void GameSystem::gameLoop() {

		while ( !this->quitGame ) {

			this->input();

			this->update();

			SDL_RenderClear( this->renderer );

			this->render();

			SDL_RenderPresent( this->renderer );
		}

		this->close();

	}

	void GameSystem::printOK() {
		printf( "OK\n" );
	}

}
