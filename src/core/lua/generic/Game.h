#pragma once

#include "Level.h"


namespace LuaGen {


	class Game {

	public:

		Game( const char* _name ) {
			level = new Level();
			name = _name;
		};

		~Game() {
			//delete level;
		}

		void Init() {};

		const char* name;

		Level* level;

	};

}

