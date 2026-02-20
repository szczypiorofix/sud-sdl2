#pragma once

#include <lua.hpp>
#include "../objects/LuaGame.h"



class GameParser {

public:
	static void RegisterObject(lua_State* L);
	static int _new(lua_State* L);
	static int _destroy(lua_State* L);
	static int _tostring(lua_State* L);
	static int _concatstring(lua_State* L);
	static int _index(lua_State* L);
	static int _newindex(lua_State* L);
	static LuaGame* GetGame(lua_State* L, const char* gameName);

	static int Init(lua_State* L);

};

