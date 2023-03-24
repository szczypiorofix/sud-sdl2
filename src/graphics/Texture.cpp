#include "Texture.h"


Texture::Texture( std::string fileName, SDL_Renderer* renderer ) {
	texture = NULL;
	this->fileName = fileName;
	this->renderer = renderer;
	width = 0;
	height = 0;
	Load();
}


Texture::~Texture( void ) {
	if ( texture != nullptr ) {
		printf( "Deleting texure '%s'\n", fileName.c_str() );
		SDL_DestroyTexture( texture );
	}
}

void Texture::draw( SDL_Rect src, SDL_Rect dest ) {
	SDL_RenderCopy( renderer, texture, &src, &dest );
}

void Texture::draw( SDL_Rect src, SDL_Rect dest, SDL_Color color ) {
	SDL_SetTextureColorMod( texture, color.r, color.g, color.b );
	SDL_RenderCopy( renderer, texture, &src, &dest );
}

void Texture::Load( void ) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( fileName.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load image '%s'! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError() );
	} else {
		
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if ( newTexture == NULL ) {
			printf( "Unable to create texture from '%s'! SDL Error: %s\n", fileName.c_str(), SDL_GetError() );
			exit( 1 );
		}
		SDL_FreeSurface( loadedSurface );
	}
	texture = newTexture;
	SDL_QueryTexture( texture, NULL, NULL, &width, &height );
	//printf("Loaded texture %s, size= %i:%i\n", fileName.c_str(), width, height);
}
