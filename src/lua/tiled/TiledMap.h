#pragma once
#include <string>
#include <vector>
extern "C" {
	#include <lua542/lua.hpp>
}
#include "TiledSpriteSheet.h"



struct TileSet {
public:
	std::string mName;
	int mFirstGid;
	std::string mFileName;
	std::string mExportFileName;
	TiledSpriteSheet* mExportSpriteSheet;
	TileSet() : mName(""), mFirstGid(0), mFileName(""), mExportFileName(""), mExportSpriteSheet(nullptr) {}
};


namespace TileLayeType {
	enum LayerType {
		TILE,
		OBJECT,
		IMAGE
	};
}


struct ObjectGroupObjectProperties {
	bool isPortal;
};


struct ObjectGroupObject {
	int id;
	std::string name;
	std::string type;
	std::string shape;
	int x;
	int y;
	int width;
	int height;
	int rotation;
	int gId;
	bool visible;
	ObjectGroupObjectProperties properties;
};


struct TileLayer {
public:
	std::string mType;
	TileLayeType::LayerType mLayerType;
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	int mId;
	std::string mName;
	std::string mClass;
	bool mVisible;
	float mOpacity;
	float mOffsetX;
	float mOffsetY;
	float mParalaxX;
	float mParalaxY;
	std::vector<int> mData;
	std::vector<ObjectGroupObject> mObjects;
	TileLayer() : mType(""), mLayerType(TileLayeType::TILE), mX(0), mY(0), mWidth(0), mHeight(0), mId(0), mName(""), mClass(""), mVisible(false), mOpacity(0.0f)
		, mOffsetX(0.0f), mOffsetY(0.0f), mParalaxX(0.0f), mParalaxY(0.0f), mData({}), mObjects({}) {}
};


class TiledMap {

public:

	TiledMap(std::string _fileName, lua_State* _L);
	~TiledMap(void);

	int mWidth;
	int mHeight;
	int mTileWidth;
	int mTileHeight;
	int mNextLeyerId;
	int mNextObjectId;
	std::vector<TileSet> mTileSets;
	std::vector<TileLayer> mTileLayers;

private:
	lua_State* L;
	std::string fileName;

	void Parse(void);

	std::vector<TileSet> TableGetTileSets(lua_State* _L, int _topStack, const char* _fieldName);
	std::vector<TileLayer> TableGetTileLayers(lua_State* _L, int _topStack, const char* _fieldName);

};

