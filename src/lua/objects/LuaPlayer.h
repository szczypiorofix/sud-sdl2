#pragma once

#include <lua.hpp>

#include <string>



class LuaPlayer {

public:

	LuaPlayer();
	LuaPlayer(std::string _name, int x, int y, unsigned int width, unsigned int height);
	LuaPlayer(const LuaPlayer& _player);

	~LuaPlayer();

	LuaPlayer& operator=(const LuaPlayer& _level);

	unsigned int width;
	unsigned int height;

	int x;
	int y;

	std::string name;

	//int Move(lua_State* L);

	int Draw();

	int (LuaPlayer::* Move)() = NULL;

};

