#pragma once

#include <string>

namespace LuaGen {


	class Level {

	public:

		Level() {
			name = "default_level_name";
			width = 0;
			height = 0;
			content = "...content...";
		}

		Level( const char* _name, int _width, int _height, const char* _content ) : name(_name), width(_width), height(_height), content(_content) {
		};

		Level( const Level& _level) {
			this->name = _level.name;
			this->width = _level.width;
			this->height = _level.height;
			this->content = _level.content;
		}

		std::string name;
		std::string content;
		int width;
		int height;

	};

}
