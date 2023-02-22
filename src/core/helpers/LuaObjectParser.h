#pragma once
#include <lua535/lua.hpp>


typedef struct Level {
	int sizeX;
	int sizeY;
	const char* content;


	Level() {
		this->sizeX = 0;
		this->sizeY = 0;
		this->content = "";
	}

	Level( int sx, int sy, const char* c ) {
		this->sizeX = sx;
		this->sizeY = sy;
		this->content = c;
	}
} Level;




class LuaObjectParser {

public:

	static Level* GetLevel( lua_State* L, const char* objectName );



};

