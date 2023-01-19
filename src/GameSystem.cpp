#include "GameSystem.h"


namespace SUD {

	GameSystem::GameSystem( void ) {
		this->window = NULL;
		this->renderer = NULL;
		this->inputs = new Inputs();

		this->fontTexture = NULL;
		this->font = NULL;

		this->scene = NULL;
		
		this->quitGame = false;
	}

	GameSystem::~GameSystem( void ) {}


	void GameSystem::close( void ) {
		this->scene->unload();

		SDL_DestroyRenderer( this->renderer );
		SDL_DestroyWindow( this->window );
		this->window = NULL;
		this->renderer = NULL;

		IMG_Quit();
		SDL_Quit();
	}

	void GameSystem::launch( void ) {
		this->initMainSDLModule();
		this->initSDLSettings();
		this->initWindow();
		this->initRenderer();
		this->initGraphics();

		this->loadAssets();

		this->gameLoop();
	}

	void GameSystem::initMainSDLModule( void ) {
		printf( "SYSTEM: initializing SDL - " );
		if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}
		this->printOK();
	}

	void GameSystem::initSDLSettings( void ) {
		printf( "SYSTEM: Initializing linear texture filtering - " );
		if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		this->printOK();
	}

	void GameSystem::initWindow( void ) {
		printf( "SYSTEM: Initializing window - " );
		this->window = SDL_CreateWindow( APP_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if ( this->window == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}
		this->printOK();
	}

	void GameSystem::initRenderer( void ) {
		printf( "SYSTEM: Initializing renderer - " );
		this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );
		if ( this->renderer == NULL ) {
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			exit( 1 );
		}

		SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );
		this->printOK();
	}

	void GameSystem::initGraphics( void ) {
		printf( "SYSTEM: Initializing images subsystems - " );
		int imgFlags = IMG_INIT_PNG;
		if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			exit( 1 );
		}
		this->printOK();
	}

	void GameSystem::loadAssets( void ) {

		printf( "SYSTEM: loading assets ...\n" );

		printf("SYSTEM: Loading font ... ");
		this->fontTexture = new Texture( DIR_RES_FONTS + "vingue.png", this->renderer );
		this->font = new Font( "vingue", this->fontTexture );
		this->printOK();

		printf("SYSTEM: Loading 'first_scene' ... ");
		this->scene = new Scene( "first_scene", this->renderer );
		this->scene->addSpriteSheet( DIR_RES_IMAGES + "spritesheet.png", 32, 32);
		this->printOK();

		this->scene->load();

	}

	void GameSystem::input( void ) {
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

	void GameSystem::update( void ) {

	}

	void GameSystem::render( void ) {
		//this->scene->draw();
		this->font->draw( "single user DUNGEON", 50, 50, 0.35f );
	}

	void GameSystem::gameLoop( void ) {

		while ( !this->quitGame ) {
			this->input();
			this->update();

			// Clear renderer
			SDL_RenderClear( this->renderer );

			// draw everything
			this->render();

			// Update screen
			SDL_RenderPresent( this->renderer );
		}

		this->close();

	}

	void GameSystem::printOK( void ) {
		printf( "OK\n" );
	}

}
