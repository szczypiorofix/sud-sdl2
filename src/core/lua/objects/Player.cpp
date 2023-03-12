#include "Player.h"



LUA::Object::Player::Player() {
	name = "...";
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

LUA::Object::Player::Player(std::string _name, int _x, int _y, unsigned int _width, unsigned int _height) : name(_name), x(_x), y(_y), width(_width), height(_height) {

}

LUA::Object::Player::Player(const Player& _player) {
	this->name = _player.name;
	this->x = _player.x;
	this->y = _player.y;
	this->width = _player.width;
	this->height = _player.height;
}

LUA::Object::Player::~Player() {
	name = "";
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

LUA::Object::Player& LUA::Object::Player::operator=(const Player& _player) {
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

int LUA::Object::Player::OnDraw(lua_State* L) {
	printf("PLAYER:OnDraw call\n");
	return 0;
}
