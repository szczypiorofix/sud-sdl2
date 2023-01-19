#include "Texture.h"


Texture::Texture( std::string fileName, SDL_Renderer* renderer ) {
	this->texture = NULL;
	this->fileName = fileName;
	this->renderer = renderer;
	this->load();
}


Texture::~Texture( void ) {}

void Texture::draw( SDL_Rect src, SDL_Rect dest ) {
	SDL_RenderCopy( this->renderer, this->texture, &src, &dest );
}

void Texture::load( void ) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( this->fileName.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", this->fileName.c_str(), IMG_GetError() );
	} else {
		newTexture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
		if ( newTexture == NULL ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", this->fileName.c_str(), SDL_GetError() );
		}
		SDL_FreeSurface( loadedSurface );
	}
	this->texture = newTexture;
}
