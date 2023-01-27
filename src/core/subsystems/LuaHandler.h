#pragma once

#include <lua535/lua.hpp>
#include <iostream>
#include <vector>



class LuaHandler {



public:
	LuaHandler();

	~LuaHandler( void );

	bool LoadFile(const std::string fileName);

	bool ProcessText(const char* content);


	bool GetGlobal( const char* name );

	bool GetInt( const char* variableName, int& value );

	bool GetFunctionStringTuple( const char* functionName, std::vector<std::string>& returnValues, const int returnValuesCounter );

	bool GetFunctionIntValue( const char* functionName, int& value );

	void Close(void);


private:
	lua_State* luaState;

	void Open(void);

};
