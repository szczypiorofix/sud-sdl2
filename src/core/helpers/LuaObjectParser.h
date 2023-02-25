#pragma once

extern "C" {
	#include <lua542/lua.hpp>
}
#include <sstream>
#include <assert.h>



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






struct Sprite {
	int x;
	int y;

	Sprite() : x(0), y(0) {
	}

	~Sprite() {
	}

	void Move(int velX, int velY) {
		x += velX;
		y += velY;
	}

	void Draw() {
		printf("Sprite %p, x = %d, y = %d\n", this, x, y);
	}

};






class LuaObjectParser {

public:

	static Level* GetLevel( lua_State* L, const char* objectName );

	
	static void RegisterSpriteObject(lua_State* L);
	static int CreateSprite(lua_State* L);
	static int DestroySprite(lua_State* L);
	static int PrintSprite(lua_State* L);
	static int DrawSprite(lua_State* L);
	static int MoveSprite(lua_State* L);

	static Sprite* GetSprite(lua_State* L, const char* objectName);
};


