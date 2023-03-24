#pragma once

extern "C" {
	#include <lua542/lua.hpp>
}
#include "../objects/LuaPlayer.h"


class PlayerParser {

public:
	static void RegisterObject(lua_State* L);
	static int _new(lua_State* L);
	static int _destroy(lua_State* L);
	static int _tostring(lua_State* L);
	static int _index(lua_State* L);
	static int _newindex(lua_State* L);
	static LuaPlayer* GetPlayer(lua_State* L, const char* playerName);
			
	static int Move(lua_State* L);

	static int MovePlayer(lua_State* L);

};

