#pragma once

#include <string>
#include <vector>
#include "Tile.h"


class Layer {

	
public:
	Layer();
	~Layer();

	int x;
	int y;
	int width;
	int height;
	int id;
	std::string name;
	bool visible;
	float offsetX;
	float offsetY;
	float paralaxX;
	float paralaxY;
	std::string spriteSheetId;
	std::vector<Tile*> data;

};

