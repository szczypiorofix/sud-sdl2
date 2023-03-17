#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "../scene/UI.h"
//#include "../graphics/Spritesheet.h"
#include "../lua/objects/Level.h"


class Scene {

public:

	Scene( std::string name, SDL_Renderer* renderer );

	~Scene( void );


	void Load();

	void AddUIObject( std::string id, UI* uiObject );

	void SetLevel(LUA::Object::Level* level);

	void Input( SDL_Event* event );
	void Update( double dt );
	void Draw( void );
	void Unload( void );

private:

	std::string name;

	SDL_Renderer* renderer;

	std::map<std::string, UI*> gameObjectsUI;

	LUA::Object::Level* level;

};

