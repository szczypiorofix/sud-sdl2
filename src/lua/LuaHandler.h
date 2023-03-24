#pragma once

#include <iostream>
#include <vector>
#include "objects/LuaGame.h"
#include "tiled/TiledMap.h"


class LuaHandler {

public:
	LuaHandler();
	~LuaHandler(void);

	bool RunScript( const std::string fileName );
	bool LoadLuaMap( const std::string fileName );
	bool RunTestScript( const std::string fileName );

	void Close(void);

	LuaGame* GetGame();

	TiledMap* GetTiledMap();

private:
	lua_State* L;

	void Open(void);

	void RegisterObjects();
	void RetrieveObjects();


	void RegisterTestObjects();
	void RetrieveTestObject();

	LuaGame* game;
	LuaPlayer* player;

	TiledMap* tiledMap;

};

