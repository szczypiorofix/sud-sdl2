#include "LuaGame.h"



LuaGame::LuaGame(const char* _name) {
	this->name = _name;
	this->level = nullptr;
	this->windowWidth = DEFAULT_WINDOW_WIDTH;
	this->windowHeight = DEFAULT_WINDOW_HEIGHT;
}

LuaGame::LuaGame(const LuaGame& _game) {
	this->name = _game.name;
	this->windowWidth = _game.windowWidth;
	this->windowHeight = _game.windowHeight;
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
	this->level = _game.level;
	return *this;
}

int LuaGame::Init( int _windowWidth, int _windowHeight) {
	this->windowWidth = _windowWidth;
	this->windowHeight = _windowHeight;
	//printf("Game:Init() called. Window size, width=%i, height=%i\n", this->windowWidth, this->windowHeight);
	return 1;
}
