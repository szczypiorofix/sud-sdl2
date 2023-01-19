#include "Spritesheet.h"


Spritesheet::Spritesheet(std::string fileName, SDL_Renderer* renderer, int tileWidth, int tileHeight) {
	this->fileName = fileName;
	this->renderer = renderer;
	this->texture = NULL;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->tilesX = 0;
	this->tilesY = 0;
}



Spritesheet::~Spritesheet( void ) { }




void Spritesheet::load( void ) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( this->fileName.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load spritesheet %s! SDL_image Error: %s\n", this->fileName.c_str(), IMG_GetError() );
	} else {
		newTexture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
		if ( newTexture == NULL ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", this->fileName.c_str(), SDL_GetError() );
			exit(1);
		}
		SDL_FreeSurface( loadedSurface );
	}
	this->texture = newTexture;

	// getting texture size
	SDL_QueryTexture(this->texture, nullptr, nullptr, &this->textureWidth, &this->textureHeight );

	// calculating tiles
	this->tilesX = this->textureWidth / this->tileWidth;
	this->tilesY = this->textureHeight / this->tileHeight;

	printf("Testure %s %ipx : %ipx, tiles: %i:%i\n", this->fileName.c_str(), this->textureWidth, this->textureHeight, this->tilesX, this->tilesY);
}


void Spritesheet::draw( void ) {
	if ( this->texture == NULL ) {
		printf("Spritesheet texture is NULL !!!");
		exit( 1 );
	}
	SDL_RenderCopy( this->renderer, this->texture, NULL, NULL );
}


void Spritesheet::unload( void ) {
	if ( this->texture != NULL ) {
		SDL_DestroyTexture( this->texture );
	}
	this->texture = NULL;
}
