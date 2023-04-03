#include "LuaGame.h"



LuaGame::LuaGame(const char* _name) {
	this->name = _name;
	this->level = nullptr;
	this->windowWidth = DEFAULT_WINDOW_WIDTH;
	this->windowHeight = DEFAULT_WINDOW_HEIGHT;
	this->amountOfTicks = 60.0;
	this->fpsCap = false;
	this->fullScreen = false;
	this->vSync = false;
}

LuaGame::LuaGame(const LuaGame& _game) {
	this->name = _game.name;
	this->windowWidth = _game.windowWidth;
	this->windowHeight = _game.windowHeight;
	this->amountOfTicks = _game.amountOfTicks;
	this->fpsCap = _game.fpsCap;
	this->fullScreen = _game.fullScreen;
	this->vSync = _game.vSync;
	if (_game.level != nullptr) {
		this->level = new LuaLevel(*(_game.level));
	}
	else {
		printf("WARNING!!! Trying to assign null pointer (game->level == nullptr) !\n");
		this->level = new LuaLevel();
	}
}

LuaGame::~LuaGame() {
}

LuaGame& LuaGame::operator=(const LuaGame& _game) {
	if (this == &_game) {
		return *this;
	}
	this->name = _game.name;
	this->windowWidth = _game.windowWidth;
	this->windowHeight = _game.windowHeight;
	this->amountOfTicks = _game.amountOfTicks;
	this->fpsCap = _game.fpsCap;
	this->fullScreen = _game.fullScreen;
	this->level = _game.level;
	this->vSync = _game.vSync;
	return *this;
}

int LuaGame::Init( int _windowWidth, int _windowHeight, double _amoutOfTicks, bool _fullScreen, bool _fpsCap, bool _vSync ) {
	this->windowWidth = _windowWidth;
	this->windowHeight = _windowHeight;
	this->amountOfTicks = _amoutOfTicks;
	this->fullScreen = _fullScreen;
	this->fpsCap = _fpsCap;
	this->vSync = _vSync;
	//printf("Game:Init() called. Window size, width=%i, height=%i\n", this->windowWidth, this->windowHeight);
	return 1;
}
