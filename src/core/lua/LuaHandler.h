#pragma once

#include <iostream>
#include <vector>
#include "parsers/Parser.h"
#include "objects/Game.h"



namespace LUA {

	class LuaHandler {

	public:
		LuaHandler();

		~LuaHandler(void);

		bool RunScript(const std::string fileName);

		bool ProcessText(const char* content);


		bool GetGlobal(const char* name);

		bool GetInt(const char* variableName, int& value);

		bool GetFunctionStringTuple(const char* functionName, std::vector<std::string>& returnValues, const int returnValuesCounter);

		bool GetFunctionIntValue(const char* functionName, int& value);

		void Close(void);

		LUA::Object::Game* GetGame();

	private:
		lua_State* L;

		void Open(void);

		void BeforeRunningScript();
		void AfterRunningScript();

		LUA::Object::Game* game;

		LUA::Object::Player* player;

	};

}
