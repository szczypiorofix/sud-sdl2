#pragma once

#include <string>


class SpriteAtlas {

public:

	SpriteAtlas();
	~SpriteAtlas(void);

	std::string name;
	int firstGid;
	std::string exportFileName;
	int tileWidth;
	int tileHeight;
	std::string imagePath;
	int imageWidth;
	int columns;
	int imageHeight;
	int tileCount;

};

