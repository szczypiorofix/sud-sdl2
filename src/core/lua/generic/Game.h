#pragma once

#include "Level.h"


namespace LuaGen {


	class Game {

	public:

		Game( const char* _name ) {
			level = new Level();
			this->name = _name;
		};

		Game( const Game& _game ) {
			printf("Game - copy constructor called.\n");
			this->name = _game.name;
			this->level = new Level( *(_game.level) );
		}

		~Game() {
			printf("Game - destructor called.\n");
			delete level;
		}


		Game& operator=(const Game& _game) {
			printf("Game - assign operator called.\n");
			if ( this == &_game ) {
				return *this;
			}
			this->name = _game.name;
			return *this;
		}


		std::string name;

		Level* level;

	};

}

