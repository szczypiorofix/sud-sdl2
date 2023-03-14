#include "Game.h"
#include "../parsers/Parser.h"

using namespace LUA::Object;


Game::Game(const char* _name) {
	this->name = _name;
	this->level = nullptr;
	this->windowWidth = DEFAULT_WINDOW_WIDTH;
	this->windowHeight = DEFAULT_WINDOW_HEIGHT;
}


Game::Game(const Game& _game) {
	this->name = _game.name;
	this->windowWidth = _game.windowWidth;
	this->windowHeight = _game.windowHeight;
	if (_game.level != nullptr) {
		this->level = new Level(*(_game.level));
	}
	else {
		printf("WARNING!!! Trying to assign null pointer (game->level == nullptr) !\n");
		this->level = new Level();
	}
}


Game::~Game() {
	//printf("Game - destructor called.\n");
	//delete level;
}


Game& Game::operator=(const Game& _game) {
	if (this == &_game) {
		return *this;
	}
	this->name = _game.name;
	this->windowWidth = _game.windowWidth;
	this->windowHeight = _game.windowHeight;
	this->level = _game.level;
	return *this;
}

int Game::Init( int windowWidth, int windowHeight) {
	printf("Game:Init() called. Window size, width=%i, height=%i\n", windowWidth, windowHeight);

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	return 1;
}



