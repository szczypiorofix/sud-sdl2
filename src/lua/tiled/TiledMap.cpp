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
        while (lua_next(L, -2) != 0) { // -2, because we have table at -1
            int tableSetTop = lua_gettop(L);
            if (lua_istable(L, -1)) {
                
                std::string type = LuaHelper::TableGetString(L, "type");
                TileLayeType::LayerType layerType = TileLayeType::TILE;

                int x = 0;
                int y = 0;
                int width = 0;
                int height = 0;

                std::vector<int> data{};
                std::vector<ObjectGroupObject> objects;


                // TILES
                if (type == "tilelayer") {
                    layerType = TileLayeType::TILE;

                    x = LuaHelper::TableGetInt(L, "x");
                    y = LuaHelper::TableGetInt(L, "y");
                    width = LuaHelper::TableGetInt(L, "width");
                    height = LuaHelper::TableGetInt(L, "height");

                    // data
                    lua_getfield(L, -1, "data");
                    if (lua_istable(L, -1)) {
                        lua_pushnil(L);
                        while (lua_next(L, -2) != 0) {
                            lua_Number n = lua_tonumber(L, -1);
                            data.push_back((int)n);
                            lua_pop(L, 1);
                        }
                    }
                    lua_remove(L, -1);
                }


                // OBJECTS
                else if (type == "objectgroup") {
                    layerType = TileLayeType::OBJECT;

                    // parse objects ...

                    lua_getfield(L, -1, "objects");
                    if (lua_istable(L, -1)) {

                        lua_pushnil(L);
                        while (lua_next(L, -2) != 0) {
                            
                            if (lua_istable(L, -1)) {

                                ObjectGroupObject obj = {};

                                int _id = LuaHelper::TableGetInt(L, "id");
                                std::string _name = LuaHelper::TableGetString(L, "name");
                                std::string _type = LuaHelper::TableGetString(L, "type");
                                std::string shape = LuaHelper::TableGetString(L, "shape");
                                int _x = LuaHelper::TableGetInt(L, "x");
                                int _y = LuaHelper::TableGetInt(L, "y");
                                int _width = LuaHelper::TableGetInt(L, "width");
                                int _height = LuaHelper::TableGetInt(L, "height");
                                int _rotation = LuaHelper::TableGetInt(L, "rotation");
                                int _gid = LuaHelper::TableGetInt(L, "gid");
                                bool _visible = LuaHelper::TableGetBool(L, "visible");

                                ObjectGroupObjectProperties properties = {};

                                lua_getfield(L, -1, "properties");
                                if (lua_istable(L, -1)) {
                                    lua_pushnil(L);
                                    while (lua_next(L, -2) != 0) {
                                        properties.isPortal = lua_toboolean(L, -1);
                                        lua_pop(L, 1);
                                    }
                                }

                                lua_remove(L, -1);

                                obj.id = _id;
                                obj.name = _name;
                                obj.type = _type;
                                obj.shape = shape;
                                obj.x = _x;
                                obj.y = _y;
                                obj.width = _width;
                                obj.height = _height;
                                obj.rotation = _rotation;
                                obj.gId = _gid;
                                obj.visible = _visible;
                                obj.properties = properties;

                                objects.push_back(obj);
                            }

                            lua_pop(L, 1);
                        }
                    }

                    lua_remove(L, -1);

                }


                // IMAGES
                else if (type == "imagelayer") {
                    layerType = TileLayeType::IMAGE;
                }


                // GROUPS
                else {
                    // group layer ...
                }

                //lua_re/move(L, -1);

                int id = LuaHelper::TableGetInt(L, "id");
                std::string name = LuaHelper::TableGetString(L, "name");
                std::string _class = LuaHelper::TableGetString(L, "class");
                bool visible = LuaHelper::TableGetBool(L, "visible");
                float opacity = LuaHelper::TableGetFloat(L, "opacity");
                float offsetx = LuaHelper::TableGetFloat(L, "offsetx");
                float offsety = LuaHelper::TableGetFloat(L, "offsety");
                float parallaxx = LuaHelper::TableGetFloat(L, "parallaxx");
                float parallaxy = LuaHelper::TableGetFloat(L, "parallaxy");

                TileLayer tempTileLayer{};
                tempTileLayer.mX = x;
                tempTileLayer.mY = y;
                tempTileLayer.mType = type;
                tempTileLayer.mLayerType = layerType;
                tempTileLayer.mWidth = width;
                tempTileLayer.mHeight = height;
                tempTileLayer.mId = id;
                tempTileLayer.mName = name;
                tempTileLayer.mClass = _class;
                tempTileLayer.mVisible = visible;
                tempTileLayer.mOpacity = opacity;
                tempTileLayer.mOffsetX = offsetx;
                tempTileLayer.mOffsetY = offsety;
                tempTileLayer.mParalaxX = parallaxx;
                tempTileLayer.mParalaxY = parallaxy;
                tempTileLayer.mData = data;
                tempTileLayer.mObjects = objects;
                tileLayers.push_back(tempTileLayer);

                lua_settop(L, tableSetTop);
            }
            lua_pop(L, 1); // remove value, keep key for lua_next
        }
    }
    return tileLayers;
}
