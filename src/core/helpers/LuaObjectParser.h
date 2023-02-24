#pragma once

extern "C" {
	#include <lua542/lua.hpp>
}



struct Level {
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
};




class LuaObjectParser {

public:

	static Level* GetLevel( lua_State* L, const char* objectName );



};

