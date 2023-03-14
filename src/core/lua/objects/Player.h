#pragma once

extern "C" {
	#include <lua542/lua.hpp>
}

#include <string>


namespace LUA {

	namespace Object {

		class Player {

		public:

			Player();
			Player(std::string _name, int x, int y, unsigned int width, unsigned int height);
			Player(const Player& _player);

			~Player();

			Player& operator=(const Player& _level);

			unsigned int width;
			unsigned int height;

			int x;
			int y;

			std::string name;

			int Move(lua_State* L);

			int Draw();


			//int (Player::* Move)(float, char, char) = NULL;

		};
	}

}

