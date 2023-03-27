#pragma once

#include <string>
#include <vector>


struct TileAnimation {
	int tileId;
	int duration;
	TileAnimation() : tileId(0), duration(0) { }
};

class Tile {

public:
	Tile();
	~Tile();

	int tileId;
	int firstGid;
	int x;
	int y;
	std::string spriteSheetId;
	bool isAnimated;
	std::vector<TileAnimation> animation;

	void Update(float dt);

	void Draw();

	int animCounter;

private:
	
	int animC;

};

