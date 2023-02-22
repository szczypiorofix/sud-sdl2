#include "LuaObjectParser.h"
#include <stdio.h>



Level* LuaObjectParser::GetLevel( lua_State* L, const char* objectName ) {
	Level* level = new Level();
	
	if (L == nullptr) {
		return nullptr;
	}

	lua_getglobal( L, objectName );
    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "sizeX");
        lua_Number sizeX = lua_tonumber(L, -1);
        lua_getfield(L, -2, "sizeY");
        lua_Number sizeY = lua_tonumber(L, -1);
        lua_getfield(L, -3, "content");
        const char* content = lua_tostring(L, -1);

        level->sizeX = (int)sizeX;
        level->sizeY = (int)sizeY;
        level->content = content;

        printf("Level : sizeX=%i, sizeY=%i, content=%s\n", (int)sizeX, (int)sizeY, content );
    }
    else {
        printf("Lua object is not a table!\n");
    }


	return level;
}
