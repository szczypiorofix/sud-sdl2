#pragma once

#include <string>
#include <vector>
extern "C" {
	#include <lua542/lua.hpp>
}



struct TileOffset {

public:
	int x;
	int y;
	TileOffset(): x(0), y(0) { };
};


struct TiledGrid {
public:
	std::string orientation;
	int width;
	int height;
	TiledGrid() : orientation(""), width(0), height(0) {	};
};


struct TiledAnimation {
public:
	int mTileId;
	int mDuration;
	TiledAnimation() : mTileId(0), mDuration(0) { };
};

struct TiledTile {
public:
	int mId;
	std::vector<TiledAnimation> mAnimation;
	TiledTile() : mId(0), mAnimation({}) { };
};


class TiledSpriteSheet {

public:

	TiledSpriteSheet(std::string _fileName);
	~TiledSpriteSheet(void);

	std::string mName;
	int mTileWidth;
	int mTileHeight;
	int mSpacing;
	int mMargin;
	int mColumns;
	std::string mImage;
	int mImageWidth;
	int mImageHeight;
	TileOffset mTileOffset;
	TiledGrid mGrid;
	int mTileCount;
	std::vector<TiledTile> mTiles;

	void Parse(lua_State* _L);
	std::vector<TiledTile> TableGetTiles(lua_State* _L, int _topStack, const char* _fieldName);

private:

	std::string fileName;

};
