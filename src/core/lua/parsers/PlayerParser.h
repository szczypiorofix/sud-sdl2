#pragma once


#include "Parser.h"
#include "../objects/Player.h"



namespace LUA {

	namespace Parser {

		class PlayerParser {

		public:
			static void RegisterObject(lua_State* L);
			static int _new(lua_State* L);
			static int _destroy(lua_State* L);
			static int _tostring(lua_State* L);
			static int _index(lua_State* L);
			static int _newindex(lua_State* L);
			static LUA::Object::Player* GetPlayer(lua_State* L, const char* playerName);
			
			static int Move(lua_State* L);

			static int MovePlayer(lua_State* L);

		};

	}

}






