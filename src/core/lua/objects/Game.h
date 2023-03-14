#pragma once

#include "Player.h"
#include "Level.h"


namespace LUA {

	namespace Object {

		class Game {

		public:

			int const static DEFAULT_WINDOW_WIDTH = 800;
			int const static DEFAULT_WINDOW_HEIGHT = 600;

			Game(const char* _name);

			Game(const Game& _game);

			~Game();

			Game& operator=(const Game& _game);

			std::string name;

			int windowWidth;
			int windowHeight;

			Level* level;

			int Init( int windowWidth, int windowHeight );

		};

	}

}
