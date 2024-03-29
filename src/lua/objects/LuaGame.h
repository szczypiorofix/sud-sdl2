#pragma once

#include "LuaPlayer.h"
#include "LuaLevel.h"


class LuaGame {

public:

	int const static DEFAULT_WINDOW_WIDTH = 800;
	int const static DEFAULT_WINDOW_HEIGHT = 600;

	LuaGame(const char* _name);

	LuaGame(const LuaGame& _game);

	~LuaGame();

	LuaGame& operator=(const LuaGame& _game);

	std::string name;

	int windowWidth;
	int windowHeight;

	double amountOfTicks;
	bool fpsCap;
	bool fullScreen;
	bool vSync;

	LuaLevel* level;

	int Init( int _windowWidth, int _windowHeight, double _amoutOfTicks, bool _fullScreen, bool _fpsCap, bool _vSync );

};
