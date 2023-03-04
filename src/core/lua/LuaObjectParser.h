#pragma once

extern "C" {
	#include <lua542/lua.hpp>
}

#include <sstream>
#include <assert.h>

#include "generic/Game.h"


struct Sprite {
	int x;
	int y;
	std::string name;

	Sprite() : x(0), y(0), name("default_name") {
	}

	~Sprite() {
	}

	void Move(int velX, int velY) {
		x += velX;
		y += velY;
	}

	void Draw() {
		printf("Sprite %p, name=%s, x=%d, y=%d\n", this, name.c_str(), x, y);
	}

};




class LuaObjectParser {

public:

	static void TestStack( lua_State* L );


	// ............ Sprite ..................
	static void RegisterSpriteObject(lua_State* L);
	static int _newSprite(lua_State* L);
	static int _destroySprite(lua_State* L);
	static int _tostringSprite(lua_State* L);
	static int _indexSprite(lua_State* L);
	static int _newindexSprite(lua_State* L);
	static int _drawSprite(lua_State* L);
	static int _moveSprite(lua_State* L);
	static Sprite* GetSprite(lua_State* L, const char* objectName);
	// .......................................



	// Generic Lua - Game
	static void RegisterGameObject(lua_State* L);
	static int _newGame(lua_State* L);
	static int _destroyGame(lua_State* L);
	static int _tostringGame(lua_State* L);
	static int _concatstringGame(lua_State* L);
	static int _indexGame(lua_State* L);
	static int _newindexGame(lua_State* L);
	static int _runGame(lua_State* L);
	static LuaGen::Level* GetLevel(lua_State* L, const char* objectName);

	// Generic Lue - Level
	static void RegisterLevelObject(lua_State* L);
	static int _newLevel(lua_State* L);
	static int _destroyLevel(lua_State* L);
	static int _tostringLevel(lua_State* L);
	static int _indexLevel(lua_State* L);
	static int _newindexLevel(lua_State* L);
	static LuaGen::Game* GetGame(lua_State* L, const char* objectName);
};


