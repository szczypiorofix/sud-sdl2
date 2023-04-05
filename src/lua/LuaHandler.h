#pragma once

#include <iostream>
#include <vector>
#include "objects/LuaGame.h"
#include "tiled/TiledMap.h"


class LuaHandler {

public:
	LuaHandler(void);
	~LuaHandler(void);

	bool RunScript( const std::string fileName );
	bool LoadLuaMap( const std::string fileName );
	bool RunTestScript( const std::string fileName );

	void Close(void);

	LuaGame* GetGame(void);
	TiledMap* GetTiledMap(void);
	LuaPlayer* GetPlayer(void);

private:
	lua_State* L;

	void Open(void);

	void RegisterObjects(void);
	void RetrieveObjects(void);

	void RegisterTestObjects(void);
	void RetrieveTestObject(void);

	LuaGame* game;
	LuaPlayer* player;

	TiledMap* tiledMap;

};

