#include "Game.h"



LUA::Object::Game::Game(const char* _name) {
	this->name = _name;
	//this->level = new Level();
	this->level = nullptr;
}


LUA::Object::Game::Game(const Game& _game) {
	//printf("Game - copy constructor called.\n");
	this->name = _game.name;
	if (_game.level != nullptr) {
		this->level = new Level(*(_game.level));
	}
	else {
		printf("WARNING!!! Trying to assign null pointer (game->level == nullptr) !\n");
		this->level = new Level();
	}
}


LUA::Object::Game::~Game() {
	//printf("Game - destructor called.\n");
	//delete level;
}


LUA::Object::Game& LUA::Object::Game::operator=(const Game& _game) {
	//printf("Game - assign operator called.\n");
	if (this == &_game) {
		return *this;
	}
	this->name = _game.name;
	this->level = _game.level;
	return *this;
}

