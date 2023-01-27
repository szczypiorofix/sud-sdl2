#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "../entities/UI.h"
#include "../graphics/Spritesheet.h"


class Scene {

public:

	Scene( std::string name, SDL_Renderer* renderer );

	~Scene( void );


	void Load();

	void AddSpriteSheet(std::string spriteSheetName, int tileWidth, int tileHeight);

	void AddUIObject( std::string id, UI* uiObject );

	void Input( SDL_Event* event );
	void Update( double dt );
	void Draw( void );
	void Unload( void );

private:

	std::string name;

	SDL_Renderer* renderer;

	Spritesheet* spriteSheet;

	std::map<std::string, UI*> gameObjectsUI;

};

