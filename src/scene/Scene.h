#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "../scene/UI.h"
#include "../lua/objects/LuaLevel.h"
#include "../lua/LuaHandler.h"
#include "Level.h"
#include "../entities/Player.h"



class Scene {

public:
	Scene( std::string _name, SDL_Renderer* _renderer );
	~Scene( void );

	void Load();
	void AddUIObject( std::string _id, UI* _uiObject );
	void SetPlayer( Player* _player );
	void SetLevel(Level* _level);
	void Input( SDL_Event* _event );
	void Update( double _dt );
	void Draw( void );
	void Unload( void );

private:
	std::string name;
	SDL_Renderer* renderer;
	std::map<std::string, UI*> gameObjectsUI;
	Level* level;
	Player* player;
};
