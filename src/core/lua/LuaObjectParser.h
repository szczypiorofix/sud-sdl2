#pragma once

extern "C" {
	#include <lua542/lua.hpp>
}
#include <sstream>
#include "generic/Player.h"
#include "generic/Game.h"


class LuaObjectParser {

public:

	static void TestStack( lua_State* L );

	// Generic Lua - Player
	static void RegisterPlayerObject(lua_State* L);
	static int _newPlayer(lua_State* L);
	static int _destroyPlayer(lua_State* L);
	static int _indexPlayer(lua_State* L);
	static int _newindexPlayer(lua_State* L);
	static LuaGen::Player* GetPlayer(lua_State* L, const char* playerName);

	// Generic Lua - Game
	static void RegisterGameObject(lua_State* L);
	static int _newGame(lua_State* L);
	static int _destroyGame(lua_State* L);
	static int _tostringGame(lua_State* L);
	static int _concatstringGame(lua_State* L);
	static int _indexGame(lua_State* L);
	static int _newindexGame(lua_State* L);
	static LuaGen::Level* GetLevel(lua_State* L, const char* objectName);

	// Generic Lue - Level
	static void RegisterLevelObject(lua_State* L);
	static int _newLevel(lua_State* L);
	static int _destroyLevel(lua_State* L);
	static int _tostringLevel(lua_State* L);
	static int _indexLevel(lua_State* L);
	static int _newindexLevel(lua_State* L);
	static LuaGen::Game* GetGame(lua_State* L, const char* objectName);
};


