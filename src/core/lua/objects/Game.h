#pragma once

#include "Player.h"
#include "Level.h"


namespace LUA {

	namespace Object {

		class Game {

		public:

			Game(const char* _name);

			Game(const Game& _game);

			~Game();

			Game& operator=(const Game& _game);

			std::string name;

			Level* level;

		};

	}

}
