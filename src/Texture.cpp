#include "Texture.h"




Texture::Texture( std::string fileName, SDL_Renderer* renderer ) {
	this->texture = NULL;
	this->fileName = fileName;
	this->renderer = renderer;
	this->load();
}


Texture::~Texture() {}

void Texture::draw() {
	
	SDL_Rect src;
	src.x = 64;
	src.y = 64;
	src.w = 32;
	src.h = 32;

	SDL_Rect dest;
	dest.x = 20;
	dest.y = 20;
	dest.w = 50;
	dest.h = 50;

	SDL_RenderCopy( this->renderer, this->texture, &src, &dest );
}

void Texture::load() {
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
