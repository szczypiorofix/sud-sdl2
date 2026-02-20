#pragma once

#include <string>
#include <vector>
#include <lua.hpp>


class LuaHelper {

public:
	static std::string TableGetString(lua_State* _L, const char* _fieldName, int _topStack = -1);
	static int TableGetInt(lua_State* _L, const char* _fieldName, int _topStack = -1);
	static bool TableGetBool(lua_State* _L, const char* _fieldName, int _topStack = -1);
	static float TableGetFloat(lua_State* _L, const char* _fieldName, int _topStack = -1);
	static void TestStack(lua_State* L);
};
