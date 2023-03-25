#include "TiledMap.h"
#include "../LuaHelper.h"
#include "../tiled/TiledSpriteSheet.h"


TiledMap::TiledMap( std::string _fileName, lua_State* _L ) {
	this->fileName = _fileName;
	this->L = _L;
	this->mWidth = 0;
	this->mHeight = 0;
	this->mNextLeyerId = 0;
	this->mNextObjectId = 0;
	this->mTileWidth = 0;
	this->mTileHeight = 0;
	this->mTileSets = {};
	this->mTileLayers = {};
	Parse();
}


TiledMap::~TiledMap( void ) {
    for (unsigned int i = 0; i < mTileSets.size(); i++) {        
        for (unsigned int j = 0; j < mTileSets.at(i).mExportSpriteSheet->mTiles.size(); j++) {
            mTileSets.at(i).mExportSpriteSheet->mTiles.clear();
        }
        mTileSets.at(i).mExportSpriteSheet->mTiles.clear();
        delete mTileSets.at(i).mExportSpriteSheet;
    }

    for (unsigned int i = 0; i < mTileLayers.size(); i++) {
        for (unsigned int j = 0; j < mTileLayers.at(i).mData.size(); j++) {
            mTileLayers.at(i).mData.clear();
        }
    }
    mTileSets.clear();
    mTileLayers.clear();
}


void TiledMap::Parse( void ) {

    if (luaL_dofile(L, fileName.c_str()) != LUA_OK) {
        printf("LUA: Error while Tiled map file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1));
        exit(1);
    }

    if (lua_istable(L, 1)) {

        int topStack = lua_gettop(L);

        int width = LuaHelper::TableGetInt(L, "width");
        //printf("Map width=%i\n", width);
        
        int height = LuaHelper::TableGetInt(L, "height");
        //printf("Map height=%i\n", height);

        int tileWidth = LuaHelper::TableGetInt(L, "tilewidth");
        //printf("Map tilewidth=%i\n", tileWidth);
        
        int tileHeight = LuaHelper::TableGetInt(L, "tileheight");
        //printf("Map tileHeight=%i\n", tileHeight);
        
        int nextlayerid = LuaHelper::TableGetInt(L, "nextlayerid");
        //printf("Map nextlayerid=%i\n", nextlayerid);
        
        int nextobjectid = LuaHelper::TableGetInt(L, "nextobjectid");
        //printf("Map nextobjectid=%i\n", nextobjectid);

        std::string orientation = LuaHelper::TableGetString(L, "orientation");
        //printf("Map orientation=%s\n", orientation.c_str());

        std::vector<TileSet> tileSets = TableGetTileSets(L, topStack, "tilesets");
        //printf("Map tilesets size=%i\n", tileSets.size());
        lua_remove(L, -1);

        std::vector<TileLayer> tileLayers = TableGetTileLayers(L, topStack, "layers");
        //printf("Map layers size=%i\n", tileLayers.size());
        lua_remove(L, -1);

        this->mWidth = width;
        this->mHeight = height;
        this->mTileWidth = tileWidth;
        this->mTileHeight = tileHeight;
        this->mNextLeyerId = nextlayerid;
        this->mNextObjectId = nextobjectid;
        this->mTileSets = tileSets;
        this->mTileLayers = tileLayers;
    }
    else {
        printf("LUA: map script was not loaded properly!\n");
    }

}





std::vector<TileSet> TiledMap::TableGetTileSets(lua_State* _L, int _topStack, const char* _fieldName) {
    std::vector<TileSet> tileSets = {};
    lua_getfield(_L, _topStack, _fieldName);
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        int c = 0;
        while (lua_next(L, -2) != 0) { // -2, because we have table at -1
            int tableSetTop = lua_gettop(L);
            if (lua_istable(L, -1)) {
                std::string name = LuaHelper::TableGetString(L, "name");
                int firstGid = LuaHelper::TableGetInt(L, "firstgid");
                std::string filename = LuaHelper::TableGetString(L, "filename");
                std::string exportfilename = LuaHelper::TableGetString(L, "exportfilename");

                //printf("Table element %i, name=%s, firstgid=%i, filename=%s\n", c, name.c_str(), firstGid, filename.c_str());

                TileSet tempTileSet;
                tempTileSet.mFileName = filename;
                tempTileSet.mFirstGid = firstGid;
                tempTileSet.mName = name;
                tempTileSet.mExportFileName = exportfilename;

                // here - add TileSet Lua script
                tempTileSet.mExportSpriteSheet = new TiledSpriteSheet(tempTileSet.mExportFileName);
                tempTileSet.mExportSpriteSheet->Parse(L);


                tileSets.push_back(tempTileSet);

                lua_settop(L, tableSetTop);
            }
            lua_pop(L, 1); // remove value, keep key for lua_next
            c++;
        }
    }
    return tileSets;
}


std::vector<TileLayer> TiledMap::TableGetTileLayers(lua_State* _L, int _topStack, const char* _fieldName) {
    std::vector<TileLayer> tileLayers = {};
    lua_getfield(_L, _topStack, _fieldName);
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        int c = 0;

        while (lua_next(L, -2) != 0) { // -2, because we have table at -1
            int tableSetTop = lua_gettop(L);
            if (lua_istable(L, -1)) {
                std::string type = LuaHelper::TableGetString(L, "type");
                //lua_re/move(L, -1);

                int x = LuaHelper::TableGetInt(L, "x");
                //lua_remove(L, -1);

                int y = LuaHelper::TableGetInt(L, "y");
                //lua_remove(L, -1);

                int width = LuaHelper::TableGetInt(L, "width");
                //lua_remove(L, -1);

                int height = LuaHelper::TableGetInt(L, "height");
                //lua_remove(L, -1);

                int id = LuaHelper::TableGetInt(L, "id");
                //lua_remove(L, -1);

                std::string name = LuaHelper::TableGetString(L, "name");
                //lua_remove(L, -1);

                std::string _class = LuaHelper::TableGetString(L, "class");
                //lua_remove(L, -1);

                bool visible = LuaHelper::TableGetBool(L, "visible");
                //lua_remove(L, -1);

                float opacity = LuaHelper::TableGetFloat(L, "opacity");
                //lua_remove(L, -1);

                float offsetx = LuaHelper::TableGetFloat(L, "offsetx");
                //lua_remove(L, -1);

                float offsety = LuaHelper::TableGetFloat(L, "offsety");
                //lua_remove(L, -1);

                float parallaxx = LuaHelper::TableGetFloat(L, "parallaxx");
                //lua_remove(L, -1);

                float parallaxy = LuaHelper::TableGetFloat(L, "parallaxy");
                //lua_remove(L, -1);

                std::string encoding = LuaHelper::TableGetString(L, "encoding");
                //lua_remove(L, -1);

                std::vector<int> data{};
                lua_getfield(L, -1, "data");

                if (lua_istable(L, -1)) {
                    lua_pushnil(L);
                    int cd = 0;
                    while (lua_next(L, -2) != 0) {
                        lua_Number n = lua_tonumber(L, -1);
                        data.push_back((int)n);
                        lua_pop(L, 1);
                        cd++;
                    }
                }

                TileLayer tempFileLayer{};
                tempFileLayer.mX = x;
                tempFileLayer.mY = y;
                tempFileLayer.mType = type;
                tempFileLayer.mWidth = width;
                tempFileLayer.mHeight = height;
                tempFileLayer.mId = id;
                tempFileLayer.mName = name;
                tempFileLayer.mClass = _class;
                tempFileLayer.mVisible = visible;
                tempFileLayer.mOpacity = opacity;
                tempFileLayer.mOffsetX = offsetx;
                tempFileLayer.mOffsetY = offsety;
                tempFileLayer.mParalaxX = parallaxx;
                tempFileLayer.mParalaxY = parallaxy;
                tempFileLayer.mEncoding = encoding;
                tempFileLayer.mData = data;
                tileLayers.push_back(tempFileLayer);

                lua_settop(L, tableSetTop);
            }
            lua_pop(L, 1); // remove value, keep key for lua_next
            c++;
        }
    }
    return tileLayers;
}
