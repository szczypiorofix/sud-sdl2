#pragma once

#include <string>


namespace LUA {

	namespace Object {

		class Level {

		public:

			Level();
			Level(const char* _name, int _width, int _height, std::string _background, std::string _foreground);


			//Level - copy constructor
			Level(const Level& _level);

			// assign operator
			Level& operator=(const Level& _level);

			~Level();

			std::string name;
			std::string background;
			std::string foreground;
			unsigned int width;
			unsigned int height;

		};

	}

}

