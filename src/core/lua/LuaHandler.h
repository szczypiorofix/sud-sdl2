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

		void Close(void);

		LUA::Object::Game* GetGame();

	private:
		lua_State* L;

		void Open(void);

		void InitializeObjects();
		void RetrieveObjects();

		LUA::Object::Game* game;

		LUA::Object::Player* player;

	};

}
