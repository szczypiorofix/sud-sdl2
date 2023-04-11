#pragma once

#include <vector>
#include "Layer.h"
#include "../lua/tiled/TiledMap.h"
#include "../lua/tiled/TiledSpriteSheet.h"
#include "SpriteAtlas.h"
#include "../entities/Player.h"


class Level {

public:

	Level();
	~Level(void);

	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int nextLayerId;
	int nextObjectId;

	std::vector<Layer*> layers;
	std::vector<SpriteAtlas*> spriteAtlas;

	void Reload(TiledMap* _tiledMap);

	void Create(TiledMap* tiledMap);

	void Draw();
	void Update(double dt);

	Player* player;

};

