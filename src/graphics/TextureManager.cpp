#include "TextureManager.h"
#include "../core/GameSystem.h"
#include "Spritesheet.h"



TextureManager::TextureManager() {
	this->textureMap = {};
}


bool TextureManager::Load( std::string _id, std::string _fileName, int _tileWidth, int _tileHeight) {
	if (textureMap.find(_id) != textureMap.end()) {
		printf("TextureManager: Error! TextureMap %s exists!\n", _id.c_str());
		return false;
	}

	SDL_Surface* surface = IMG_Load( _fileName.c_str() );
	if ( surface == NULL ) {
		SDL_Log( "TextureManager: Failed to load surface: '%s', %s", _fileName.c_str(), SDL_GetError() );
		return false;
	}
	SDL_Log("TextureManager: image '%s' loaded successfully.\n", _fileName.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface( GameSystem::GetInstance()->GetRenderer(), surface );
	if ( texture == NULL ) {
		SDL_Log( "TextureManager: Failed to create texture from surface: %s", SDL_GetError() );
		return false;
	}
	SpriteSheet* spriteSheet = new SpriteSheet( texture, surface->w, surface->h, _tileWidth, _tileHeight );

	SDL_FreeSurface(surface);
	surface = nullptr;

	textureMap[ _id ] = spriteSheet;
	return true;
}


void TextureManager::Draw( std::string _id, int _x, int _y, int _width, int _height, SDL_RendererFlip _flip ) {
	SDL_Rect srcRect = { 0, 0, _width, _height };
	SDL_Rect dstRect = { _x, _y, _width, _height };
	SDL_RenderCopyEx( GameSystem::GetInstance()->GetRenderer(), textureMap[ _id ]->texture, &srcRect, &dstRect, 0, nullptr, _flip );
}


void TextureManager::DrawSprite( std::string _id, int _x, int _y, int _width, int _height, int _sx, int _sy, int _sw, int _sh, SDL_RendererFlip _flip ) {
	SDL_Rect srcRect = { _sx, _sy, _sw, _sh };
	SDL_Rect dstRect = { _x, _y, _width, _height };
	SDL_RenderCopyEx( GameSystem::GetInstance()->GetRenderer(), textureMap[ _id ]->texture, &srcRect, &dstRect, 0, nullptr, _flip );
}


void TextureManager::DrawSpriteIndex( std::string _id, int _x, int _y, int _width, int _height, unsigned int _index, SDL_RendererFlip _flip ) {
	SpriteSheet* sprite = textureMap[_id];
	if (sprite != nullptr) {
		int columns = sprite->columns;
		int tileWidth = sprite->tileWidth;
		int indX = ((_index) % columns) * tileWidth;
		int indY = ((_index) / columns) * sprite->tileHeight;
		SDL_Rect srcRect = { indX, indY, tileWidth, sprite->tileHeight };
		SDL_Rect dstRect = { _x, _y, _width, _height };
		SDL_RenderCopyEx(GameSystem::GetInstance()->GetRenderer(), sprite->texture, &srcRect, &dstRect, 0, nullptr, _flip);
	}
}


SpriteSheet* TextureManager::GetSpriteSheet( std::string id ) {
	return textureMap[ id ];
}


void TextureManager::Drop( std::string id ) {
	if (textureMap.at(id) != nullptr) {
		SDL_Log("TextureManager: Texture '%s' cleared.", id.c_str());
		delete textureMap[id];
		textureMap.erase(id);
	}
}


void TextureManager::Clean() {
	std::map<std::string, SpriteSheet*>::iterator it;
	for ( it = textureMap.begin(); it != textureMap.end(); it++ ) {
		delete it->second;
		SDL_Log("TextureManager: Texture '%s' cleared.", it->first.c_str());
	}
	textureMap.clear();
	SDL_Log("TextureManager: Texture map cleared.");
}
