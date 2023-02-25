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



// ==================== SPRITE =========================

void LuaObjectParser::RegisterSpriteObject(lua_State* L) {
    // New table
    lua_newtable(L);
    // Sprite table index on Lua stack 
    int spriteTableIdx = lua_gettop(L);
    lua_pushvalue(L, spriteTableIdx);
    lua_setglobal(L, "Sprite");

    // Sprite contructor
    lua_pushcfunction(L, LuaObjectParser::CreateSprite);
    lua_setfield(L, -2, "new");

    // Sprite Move method
    lua_pushcfunction(L, LuaObjectParser::MoveSprite);
    lua_setfield(L, -2, "Move");

    // Sprite Draw method
    lua_pushcfunction(L, LuaObjectParser::DrawSprite);
    lua_setfield(L, -2, "Draw");


    // Creating new metatable
    luaL_newmetatable(L, "SpriteMetaTable");

    lua_pushstring(L, "__gc"); // Garbage Collector metamethod - runs Sprite destructor
    lua_pushcfunction(L, LuaObjectParser::DestroySprite);
    lua_settable(L, -3);

    lua_pushstring(L, "__tostring"); // tostring metamethod override
    lua_pushcfunction(L, LuaObjectParser::PrintSprite);
    lua_settable(L, -3);

    lua_pushstring(L, "__index"); // seting the proper index for SpriteMetaTable
    lua_pushvalue(L, spriteTableIdx);
    lua_settable(L, -3);
}

int LuaObjectParser::CreateSprite(lua_State* L) {
	void* pointerToASprite = lua_newuserdata(L, sizeof(Sprite));
	new (pointerToASprite) Sprite();
	luaL_getmetatable(L, "SpriteMetaTable");
	assert(lua_istable(L, -1));
	lua_setmetatable(L, -2);
	printf("A new sprite has been created.\n");
	return 1;
};

int LuaObjectParser::DestroySprite(lua_State* L) {
	Sprite* sprite = (Sprite*)lua_touserdata(L, -1);
	sprite->~Sprite();
	printf("Destroy sprite\n");
	return 0;
};

int LuaObjectParser::MoveSprite(lua_State* L) {
	Sprite* sprite = (Sprite*)lua_touserdata(L, -3);
	lua_Number velX = lua_tonumber(L, -2);
	lua_Number velY = lua_tonumber(L, -1);
	sprite->Move((int)velX, (int)velY);
	return 0;
}

Sprite* LuaObjectParser::GetSprite(lua_State* L, const char* objectName) {
    lua_getglobal(L, objectName);
    Sprite* sprite = (Sprite*)lua_touserdata(L, -1);
    return sprite;
}


int LuaObjectParser::DrawSprite(lua_State* L) {
	Sprite* sprite = (Sprite*)lua_touserdata(L, -1);
	sprite->Draw();
	return 0;
};

int LuaObjectParser::PrintSprite(lua_State* L) {
	Sprite* sprite = (Sprite*)lua_touserdata(L, -1);
	std::stringstream ss;
	ss << "Sprite object memaddr=" << (void const*)sprite << ", x=" << sprite->x << ", y=" << sprite->y;
	std::string s = ss.str();
	lua_pushstring(L, s.c_str());
	return 1;
};
