#pragma once

extern "C" {
	#include <lua542/lua.hpp>
}
#include "../objects/LuaLevel.h"



class LevelParser {

public:
	static void RegisterObject(lua_State* L);
	static int _new(lua_State* L);
	static int _destroy(lua_State* L);
	static int _tostring(lua_State* L);
	static int _index(lua_State* L);
	static int _newindex(lua_State* L);
	static LuaLevel* GetLevel(lua_State* L, const char* levelName);

};
