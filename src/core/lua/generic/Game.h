#pragma once

#include "Level.h"


namespace LuaGen {


	class Game {

	public:

		Game( const char* _name ) {
			level = new Level();
			name = _name;
		};

		Game( const Game& _game ) {
			this->name = _game.name;
			this->level = new Level( *(_game.level) );
		}

		~Game() {
		}

		std::string name;

		Level* level;

	};

}

