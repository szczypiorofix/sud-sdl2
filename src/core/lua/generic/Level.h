#pragma once

#include <string>

namespace LuaGen {


	class Level {

	public:

		Level() {
			name = "default_level_name";
			width = 0;
			height = 0;
			background = "...";
			foreground = "...";
		}

		Level( const char* _name, int _width, int _height, std::string _background, std::string _foreground) : name(_name), width(_width), height(_height), background(_background), foreground(_foreground) {
		};

		//Level - copy constructor
		Level( const Level& _level) {
			this->name = _level.name;
			this->width = _level.width;
			this->height = _level.height;
			this->background = _level.background;
			this->foreground = _level.foreground;
		}

		Level& operator=(const Level& _level) {
			//printf("Level - assign operator called.\n");
			if (this == &_level) {
				return *this;
			}
			this->name = _level.name;
			this->width = _level.width;
			this->height = _level.height;
			this->foreground = _level.foreground;
			this->background = _level.background;
			return *this;
		}

		~Level() {
			name = "";
			height = 0;
			width = 0;
			background = "";
			foreground = "";
		}

		std::string name;
		std::string background;
		std::string foreground;
		unsigned int width;
		unsigned int height;

	};

}
