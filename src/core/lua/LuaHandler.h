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

		bool LoadLuaMap( const std::string fileName );

		void Close(void);

		LUA::Object::Game* GetGame();

	private:
		lua_State* L;

		void Open(void);

		void RegisterObjects();
		void RetrieveObjects();

		void RegisterMapObject();
		void RetrieveMapObject();


		std::string TableGetString( lua_State* _L, int _topStack, const char* _fieldName );
		int TableGetInt( lua_State* _L, int _topStack, const char* _fieldName );

		LUA::Object::Game* game;
		LUA::Object::Player* player;

	};

}
