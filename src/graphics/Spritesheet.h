#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


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

	SpriteSheet(SDL_Texture* _texture, int _width, int _height, int _tileWidth = 0, int _tileHeight = 0) {
		this->texture = _texture;
		this->width = _width;
		this->height = _height;
		this->tileWidth = _tileWidth;
		this->tileHeight = _tileHeight;
		this->x = 0;
		this->y = 0;
		this->tileX = _tileWidth > 0 ? _width / _tileWidth : 0;
		this->tileY = _tileHeight > 0 ? _height / _tileHeight : 0;
		this->isSprite = _tileWidth > 0 && _tileHeight > 0;
		this->columns = this->tileWidth > 0 ? this->width / this->tileWidth : 0;
	}

	~SpriteSheet() {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

};

