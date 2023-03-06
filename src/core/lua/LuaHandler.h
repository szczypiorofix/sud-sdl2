#pragma once

#include <iostream>
#include <vector>
#include "LuaObjectParser.h"
#include "generic/Game.h"



class LuaHandler {

public:
	LuaHandler();

	~LuaHandler( void );

	bool RunScript( const std::string fileName );

	bool ProcessText(const char* content);


	bool GetGlobal( const char* name );

	bool GetInt( const char* variableName, int& value );

	bool GetFunctionStringTuple( const char* functionName, std::vector<std::string>& returnValues, const int returnValuesCounter );

	bool GetFunctionIntValue( const char* functionName, int& value );

	void Close(void);

	void RegisterObject();

	LuaGen::Game* GetGame();
	LuaGen::Level* GetLevel();

private:
	lua_State* L;

	void Open(void);

	void BeforeRunningScript();
	void AfterRunningScript();

	LuaGen::Game* game;
	LuaGen::Level* level;

};
