#include "LuaPlayer.h"


LuaPlayer::LuaPlayer() {
	name = "...";
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

LuaPlayer::LuaPlayer(std::string _name, int _x, int _y, unsigned int _width, unsigned int _height) : name(_name), x(_x), y(_y), width(_width), height(_height) {

}

LuaPlayer::LuaPlayer(const LuaPlayer& _player) {
	this->name = _player.name;
	this->x = _player.x;
	this->y = _player.y;
	this->width = _player.width;
	this->height = _player.height;
}

LuaPlayer::~LuaPlayer() {
}

LuaPlayer& LuaPlayer::operator=(const LuaPlayer& _player) {
	//printf("Player - assign operator called.\n");
	if (this == &_player) {
		return *this;
	}
	this->name = _player.name;
	this->x = _player.x;
	this->y = _player.y;
	this->width = _player.width;
	this->height = _player.height;
	return *this;
}

//int LuaPlayer::Move(lua_State* L) {
//	printf("Player (C++) Move method\n");
//	return 0;
//}


int LuaPlayer::Draw() {
	printf("Player (C++) Draw method\n");
	return 12;
}
