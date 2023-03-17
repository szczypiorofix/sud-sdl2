#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>



struct SpriteSheet {

public:
		
	SDL_Texture* texture;
	int x;
	int y;
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int tileX;
	int tileY;
	bool isSprite;
	unsigned int columns;

	SpriteSheet(SDL_Texture* _texture, int _width, int _height, int _tileWidth, int _tileHeight) {
		this->texture = _texture;
		this->width = _width;
		this->height = _height;
		this->tileWidth = _tileWidth;
		this->tileHeight = _tileHeight;
		this->x = 0;
		this->y = 0;
		this->tileX = _width / _tileWidth;
		this->tileY = _height / _tileHeight;
		this->isSprite = true;
		this->columns = this->width / this->tileWidth;
	}

	SpriteSheet(SDL_Texture* _texture, int _width, int _height ) {
		this->texture = _texture;
		this->width = _width;
		this->height = _height;
		this->tileWidth = 0;
		this->tileHeight = 0;
		this->x = 0;
		this->y = 0;
		this->tileX = 0;
		this->tileY = 0;
		this->isSprite = false;
		this->columns = 0;
	}

};


class TextureManager {


public:
	static TextureManager* GetInstance() {
		static TextureManager* textureManager = nullptr;
		if ( textureManager == nullptr ) {
			textureManager = new TextureManager();
		}
		return textureManager;
	}

	bool Load( std::string _id, std::string _fileName );
	bool LoadSprite( std::string _id, std::string _fileName, int _tileWidth, int _tileHeight );
	void Drop( std::string _id );
	void Clean();
	void Draw( std::string _id, int _x, int _y, int _width, int _height, SDL_RendererFlip _flip = SDL_FLIP_NONE );
	void DrawSprite( std::string _id, int _x, int _y, int _width, int _height, int _sx, int _sy, int _sw, int _sh, SDL_RendererFlip _flip = SDL_FLIP_NONE );
	void DrawSpriteIndex( std::string _id, int _x, int _y, int _width, int _height, unsigned int _index, SDL_RendererFlip _flip = SDL_FLIP_NONE );
	
	SpriteSheet* GetSpriteSheet( std::string id );

private:
	TextureManager( void );

	std::map<std::string, SpriteSheet*> textureMap;

};
