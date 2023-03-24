#include "TiledSpriteSheet.h"
#include "../../core/Defines.h"
#include "../LuaHelper.h"




TiledSpriteSheet::TiledSpriteSheet( std::string _fileName ) {
	this->fileName = _fileName;
	this->mColumns = 0;
	this->mMargin = 0;
	this->mTileWidth = 0;
	this->mTileHeight = 0;
	this->mName = "";
	this->mImage = "";
	this->mImageWidth = 0;
	this->mImageHeight = 0;
	this->mTileOffset = {};
	this->mGrid = {};
	this->mTileCount = 0;
	this->mTiles = {};
}



TiledSpriteSheet::~TiledSpriteSheet( void ) {

}


void TiledSpriteSheet::Parse( lua_State* L ) {
	std::string fn = DIR_RES_SCRIPTS + fileName;
	if (luaL_dofile(L, fn.c_str()) != LUA_OK) {
		printf("LUA: Error while loading Tiled spritesheet file ('%s'): %s\n", fn.c_str(), lua_tostring(L, -1));
		exit(1);
	}

	//LUA::Parser::Parser::TestStack(L);
	if (lua_istable(L, 1)) {

		int topStack = lua_gettop(L);

		int tileWidth = LuaHelper::TableGetInt(L,"tilewidth");
		int tileHeight = LuaHelper::TableGetInt(L, "tileheight");
		std::string name = LuaHelper::TableGetString(L, "name");
		int spacing = LuaHelper::TableGetInt(L, "spacing");
		int margin = LuaHelper::TableGetInt(L, "margin");
		int columns = LuaHelper::TableGetInt(L, "columns");
		std::string image = LuaHelper::TableGetString(L, "image");
		int imageWidth = LuaHelper::TableGetInt(L, "imagewidth");
		int imageHeight = LuaHelper::TableGetInt(L, "imageheight");
		
		
		TileOffset tileOffset = {};
		lua_getfield(L, topStack, "tileoffset");
		if (lua_istable(L, -1)) {
			tileOffset.x = LuaHelper::TableGetInt(L, "x");
			tileOffset.y = LuaHelper::TableGetInt(L, "y");
		}
		lua_remove(L, -1);


		TiledGrid grid = {};
		lua_getfield(L, topStack, "grid");
		if (lua_istable(L, -1)) {
			grid.width = LuaHelper::TableGetInt(L, "width");
			grid.height = LuaHelper::TableGetInt(L, "height");
			grid.orientation = LuaHelper::TableGetString(L, "orientation");
		}
		lua_remove(L, -1);


		int tileCount = LuaHelper::TableGetInt(L, "tilecount");


		std::vector<TiledTile> tiles = TableGetTiles(L, topStack, "tiles");


		mTileWidth = tileWidth;
		mTileHeight = tileHeight;
		mName = name;
		mSpacing = spacing;
		mMargin = margin;
		mColumns = columns;
		mImage = image;
		mImageWidth = imageWidth;
		mImageHeight = imageHeight;
		mTileOffset = tileOffset;
		mGrid = grid;
		mTileCount = tileCount;
		mTiles = tiles;
		
		//printf("Grid orientation=%s\n", mGrid.orientation.c_str());

		//for (int i = 0; i < mTiles.size(); i++) {
		//	for (int j = 0; j < mTiles.at(i).mAnimation.size(); j++) {
		//		printf("Tile %i animation tileId=%i\n", i, mTiles.at(i).mAnimation.at(j).mTileId);
		//	}
		//}

	}

}

std::vector<TiledTile> TiledSpriteSheet::TableGetTiles(lua_State* L, int _topStack, const char* _fieldName) {
	std::vector<TiledTile> tiles;
	lua_getfield(L, _topStack, _fieldName);
	if (lua_istable(L, -1)) {
		lua_pushnil(L);
		int c = 0;

		while (lua_next(L, -2) != 0) { // -2, because we have table at -1
			TiledTile tile = {};
			tile.mId = LuaHelper::TableGetInt(L, "id");
			std::vector<TiledAnimation> animation = {};

			lua_getfield(L, -1, "animation");
			if (lua_istable(L, -1)) {
				TiledAnimation anim = {};
				int d = 0;
				lua_pushnil(L);
				while (lua_next(L, -2) != 0) {
					anim.mTileId = LuaHelper::TableGetInt(L, "tileid");
					anim.mDuration = LuaHelper::TableGetInt(L, "duration");
					animation.push_back(anim);
					lua_pop(L, 1); // remove value, keep key for lua_next
					d++;
				}
			}

			tile.mAnimation = animation;
			tiles.push_back(tile);

			lua_remove(L, -1);
			lua_pop(L, 1); // remove value, keep key for lua_next
			c++;
		}
	}

	return tiles;
}

