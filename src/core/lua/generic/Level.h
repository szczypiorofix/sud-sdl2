#pragma once


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

		const char* name;
		int width;
		int height;
		const char* content;

	};

}
