#include "LuaLevel.h"



LuaLevel::LuaLevel() {
	name = "default_level_name";
	width = 0;
	height = 0;
	background = "...";
	foreground = "...";
}


LuaLevel::LuaLevel(const char* _name, int _width, int _height, std::string _background, std::string _foreground)
	: name(_name), width(_width), height(_height), background(_background), foreground(_foreground) { }


LuaLevel::LuaLevel(const LuaLevel& _level) {
	//printf("Level - copy constructor called.\n");
	this->name = _level.name;
	this->width = _level.width;
	this->height = _level.height;
	this->background = _level.background;
	this->foreground = _level.foreground;
}


LuaLevel& LuaLevel::operator=(const LuaLevel& _level) {
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


LuaLevel::~LuaLevel() {
}

