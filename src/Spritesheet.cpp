#include "Spritesheet.h"



Spritesheet::Spritesheet( std::string fileName, SDL_Renderer* renderer ) {
	this->fileName = fileName;
	this->renderer = renderer;
	this->texture = NULL;
}



Spritesheet::~Spritesheet() { }




void Spritesheet::load() {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( this->fileName.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load spritesheet %s! SDL_image Error: %s\n", this->fileName.c_str(), IMG_GetError() );
	} else {
		newTexture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
		if ( newTexture == NULL ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", this->fileName.c_str(), SDL_GetError() );
		}
		SDL_FreeSurface( loadedSurface );
	}
	this->texture = newTexture;
}



void Spritesheet::draw() {
	if ( this->texture == NULL ) {
		printf("Spritesheet texture is NULL !!!");
		exit( 1 );
	}
	SDL_RenderCopy( this->renderer, this->texture, NULL, NULL );
}


void Spritesheet::unload() {
	if ( this->texture != NULL ) {
		SDL_DestroyTexture( this->texture );
	}
	this->texture = NULL;
}
