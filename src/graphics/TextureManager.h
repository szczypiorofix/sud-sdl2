#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include "Spritesheet.h"






class TextureManager {


public:
	static TextureManager* GetInstance() {
		static TextureManager* textureManager = nullptr;
		if ( textureManager == nullptr ) {
			textureManager = new TextureManager();
		}
		return textureManager;
	}

	bool Load( std::string _id, std::string _fileName, int _tileWidth = 0, int _tileHeight = 0);

	void Drop( std::string _id );
	void Clean();

	void Draw( std::string _id, int _x, int _y, int _width, int _height, SDL_RendererFlip _flip = SDL_FLIP_NONE );
	void DrawSprite( std::string _id, int _x, int _y, int _width, int _height, int _sx, int _sy, int _sw, int _sh, SDL_RendererFlip _flip = SDL_FLIP_NONE );
	void DrawSpriteIndex( std::string _id, int _x, int _y, int _width, int _height, unsigned int _index, SDL_RendererFlip _flip = SDL_FLIP_NONE );
	//void DrawSpriteIndexAnimation(std::string _id, int _x, int _y, int _width, int _height, unsigned int _index, Animation _animation, SDL_RendererFlip _flip = SDL_FLIP_NONE);
	
	SpriteSheet* GetSpriteSheet( std::string id );

private:
	TextureManager( void );

	std::map<std::string, SpriteSheet*> textureMap;

};
