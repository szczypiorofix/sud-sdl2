#include "TextureManager.h"
#include "../GameSystem.h"



TextureManager::TextureManager() {
	this->textureMap = {};
}

bool TextureManager::Load( std::string id, std::string fileName ) {
	SDL_Surface* surface = IMG_Load( fileName.c_str() );
	if ( surface == NULL ) {
		SDL_Log( "Failed to load surface: '%s', %s", fileName.c_str(), SDL_GetError() );
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( SUD::GameSystem::GetInstance()->GetRenderer(), surface );
	if ( texture == NULL ) {
		SDL_Log( "Failed to create texture from surface: %s", SDL_GetError() );
		return false;
	}

	textureMap[ id ] = texture;

	return true;
}


void TextureManager::Draw( std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE ) {
	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect dstRect = { x, y, width, height };
	SDL_RenderCopyEx( SUD::GameSystem::GetInstance()->GetRenderer(), textureMap[ id ], &srcRect, &dstRect, 0, nullptr, flip );
}


void TextureManager::DrawSprite( std::string id, int x, int y, int width, int height, int sx, int sy, int sw, int sh, SDL_RendererFlip flip = SDL_FLIP_NONE ) {
	SDL_Rect srcRect = { sx, sy, sw, sh };
	SDL_Rect dstRect = { x, y, width, height };
	SDL_RenderCopyEx( SUD::GameSystem::GetInstance()->GetRenderer(), textureMap[ id ], &srcRect, &dstRect, 0, nullptr, flip );
}

SDL_Texture* TextureManager::GetTexture( std::string id ) {
	return textureMap[ id ];
}


void TextureManager::Drop( std::string id ) {
	SDL_DestroyTexture( textureMap[ id ] );
	textureMap.erase( id );
}


void TextureManager::Clean() {
	std::map<std::string, SDL_Texture*>::iterator it;
	for ( it = textureMap.begin(); it != textureMap.end(); it++ ) {
		SDL_DestroyTexture(it->second);
	}
	textureMap.clear();
	SDL_Log("Texture map cleared.");
}
