#pragma once

#include <lua.hpp>


class TestObject {

public:
	int Call( lua_State* L) {
		printf("TestObject.Call() invoked! Calling callback...\n");
		return lua_pcall(L, 0, 1, 0);
	}
	
};


static int player_draw_registry_value = 0;


class TestParser {

public:
	static void RegisterObject(lua_State* L);

	static void ResolveObjects(lua_State* L);

	static int TestFunction(lua_State* L);

	static int register_player_draw(lua_State* L);

};