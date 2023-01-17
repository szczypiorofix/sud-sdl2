#pragma once

#include <lua535/lua.hpp>
#include <string>

class LuaHandler {



public:
	LuaHandler( const std::string& fileName );
	~LuaHandler( void );


private:
	lua_State* luaState;

};
