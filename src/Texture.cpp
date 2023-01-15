#include "Texture.h"




Texture::Texture( std::string fileName, SDL_Renderer* renderer ) {
	this->texture = NULL;
	this->fileName = fileName;
	this->renderer = renderer;
	this->load();
}


Texture::~Texture() {}

void Texture::draw() {
	SDL_RenderCopy( this->renderer, this->texture, NULL, NULL );
}

void Texture::load() {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( this->fileName.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", this->fileName.c_str(), IMG_GetError() );
	} else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
		if ( newTexture == NULL ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", this->fileName.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	this->texture = newTexture;
}
