#include "TextureManager.h"
#include "../GameSystem.h"



TextureManager::TextureManager() {
	this->textureMap = {};
}


bool TextureManager::Load( std::string _id, std::string _fileName ) {
	SDL_Surface* surface = IMG_Load( _fileName.c_str() );
	if ( surface == NULL ) {
		SDL_Log( "Failed to load surface: '%s', %s", _fileName.c_str(), SDL_GetError() );
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( SUD::GameSystem::GetInstance()->GetRenderer(), surface );
	if ( texture == NULL ) {
		SDL_Log( "Failed to create texture from surface: %s", SDL_GetError() );
		return false;
	}
	SpriteSheet* spriteSheet = new SpriteSheet( texture, surface->w, surface->h );

	textureMap[ _id ] = spriteSheet;

	return true;
}


bool TextureManager::LoadSprite(std::string _id, std::string _fileName, int _tileWidth, int _tileHeight) {
	SDL_Surface* surface = IMG_Load(_fileName.c_str());
	if (surface == NULL) {
		SDL_Log("Failed to load surface: '%s', %s", _fileName.c_str(), SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(SUD::GameSystem::GetInstance()->GetRenderer(), surface);
	if (texture == NULL) {
		SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
		return false;
	}
	SpriteSheet* spriteSheet = new SpriteSheet( texture, surface->w, surface->h, _tileWidth, _tileHeight );

	textureMap[_id] = spriteSheet;

	return true;
}


void TextureManager::Draw( std::string _id, int _x, int _y, int _width, int _height, SDL_RendererFlip _flip ) {
	SDL_Rect srcRect = { 0, 0, _width, _height };
	SDL_Rect dstRect = { _x, _y, _width, _height };
	SDL_RenderCopyEx( SUD::GameSystem::GetInstance()->GetRenderer(), textureMap[ _id ]->texture, &srcRect, &dstRect, 0, nullptr, _flip );
}


void TextureManager::DrawSprite( std::string _id, int _x, int _y, int _width, int _height, int _sx, int _sy, int _sw, int _sh, SDL_RendererFlip _flip ) {
	SDL_Rect srcRect = { _sx, _sy, _sw, _sh };
	SDL_Rect dstRect = { _x, _y, _width, _height };
	SDL_RenderCopyEx( SUD::GameSystem::GetInstance()->GetRenderer(), textureMap[ _id ]->texture, &srcRect, &dstRect, 0, nullptr, _flip );
}

void TextureManager::DrawSpriteIndex( std::string _id, int _x, int _y, int _width, int _height, unsigned int _index, SDL_RendererFlip _flip ) {
	SpriteSheet* sprite = textureMap[_id];
	int columns = sprite->columns;
	int tileWidth = sprite->tileWidth;
	int indX = (_index % columns) * tileWidth;
	int indY = (_index / columns) * tileWidth;
	SDL_Rect srcRect = { indX, indY, tileWidth, sprite->tileHeight };
	SDL_Rect dstRect = { _x, _y, _width, _height };
	SDL_RenderCopyEx(SUD::GameSystem::GetInstance()->GetRenderer(), sprite->texture, &srcRect, &dstRect, 0, nullptr, _flip);
}


//void TextureManager::DrawSpriteIndex(std::string _id, int _x, int _y, int _width, int _height, unsigned int _index, SDL_RendererFlip _flip = SDL_FLIP_NONE ) {
//	SpriteSheet* sprite = textureMap[_id];
//	int columns = sprite->columns;
//	int tileWidth = sprite->tileWidth;
//	int indX = (_index % columns) * tileWidth;
//	int indY = (_index / columns) * tileWidth;
//	SDL_Rect srcRect = { indX, indY, tileWidth, sprite->tileHeight };
//	SDL_Rect dstRect = { _x, _y, _width, _height };
//	SDL_RenderCopyEx(SUD::GameSystem::GetInstance()->GetRenderer(), sprite->texture, &srcRect, &dstRect, 0, nullptr, _flip);
//}


SpriteSheet* TextureManager::GetSpriteSheet( std::string id ) {
	return textureMap[ id ];
}


void TextureManager::Drop( std::string id ) {
	SDL_DestroyTexture( textureMap[ id ]->texture );
	textureMap.erase( id );
}


void TextureManager::Clean() {
	std::map<std::string, SpriteSheet*>::iterator it;
	for ( it = textureMap.begin(); it != textureMap.end(); it++ ) {
		SDL_DestroyTexture(it->second->texture);
	}
	textureMap.clear();
	SDL_Log("Texture map cleared.");
}
