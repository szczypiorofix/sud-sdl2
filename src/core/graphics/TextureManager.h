#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>


class TextureManager {


public:
	static TextureManager* GetInstance() {
		static TextureManager* textureManager = nullptr;
		if ( textureManager == nullptr ) {
			textureManager = new TextureManager();
		}
		return textureManager;
	}

	bool Load( std::string id, std::string fileName );
	void Drop( std::string id );
	void Clean();
	void Draw( std::string id, int x, int y, int width, int height, SDL_RendererFlip flip );
	void DrawSprite( std::string id, int x, int y, int width, int height,  int sx, int sy, int sw, int sh, SDL_RendererFlip flip );
	
	SDL_Texture* GetTexture( std::string id );

private:
	TextureManager( void );

	std::map<std::string, SDL_Texture*> textureMap;

};
