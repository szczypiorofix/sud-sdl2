#include "Texture.h"


Texture::Texture( std::string fileName, SDL_Renderer* renderer ) {
	texture = NULL;
	this->fileName = fileName;
	this->renderer = renderer;
	Load();
}


Texture::~Texture( void ) {}

void Texture::draw( SDL_Rect src, SDL_Rect dest ) {
	SDL_RenderCopy( this->renderer, this->texture, &src, &dest );
}

void Texture::Load( void ) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( fileName.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError() );
	} else {
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if ( newTexture == NULL ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError() );
		}
		SDL_FreeSurface( loadedSurface );
	}
	texture = newTexture;
}
