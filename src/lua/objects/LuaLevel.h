#pragma once

#include <string>


class LuaLevel {

public:

	LuaLevel();
	LuaLevel(const char* _name, int _width, int _height, std::string _background, std::string _foreground);


	//Level - copy constructor
	LuaLevel(const LuaLevel& _level);

	// assign operator
	LuaLevel& operator=(const LuaLevel& _level);

	~LuaLevel();

	std::string name;
	std::string background;
	std::string foreground;
	unsigned int width;
	unsigned int height;

};

