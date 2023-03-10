#pragma once

#include "Level.h"


namespace LuaGen {


	class Game {

	public:

		Game( const char* _name ) {
			this->name = _name;
			//this->level = new Level();
			this->level = nullptr;
		};

		Game( const Game& _game ) {
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

		~Game() {
			//printf("Game - destructor called.\n");
			//delete level;
		}


		Game& operator=(const Game& _game) {
			//printf("Game - assign operator called.\n");
			if ( this == &_game ) {
				return *this;
			}
			this->name = _game.name;
			this->level = _game.level;
			return *this;
		}


		std::string name;

		Level* level;

	};

}

