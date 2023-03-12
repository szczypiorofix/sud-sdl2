#pragma once

#include "Parser.h"
#include "../objects/Level.h"


namespace LUA {

	namespace Parser {

		class LevelParser {

		public:
			static void RegisterObject(lua_State* L);
			static int _new(lua_State* L);
			static int _destroy(lua_State* L);
			static int _tostring(lua_State* L);
			static int _index(lua_State* L);
			static int _newindex(lua_State* L);
			static LUA::Object::Level* GetLevel(lua_State* L, const char* levelName);

		};

	}

}
