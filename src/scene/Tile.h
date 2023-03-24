#pragma once

#include <string>



class Tile {

public:
	Tile();
	~Tile();

	int tileId;
	int firstGid;
	std::string spriteSheetId;
	bool isAnimated;


	void Update(float dt);

	void Draw();

};

