#include "LuaHandler.h"
#include "../Defines.h"
#include "parsers/PlayerParser.h"
#include "parsers/LevelParser.h"
#include "parsers/GameParser.h"



using namespace LUA;
using namespace LUA::Object;

LuaHandler::LuaHandler() {
    L = nullptr;
    game = nullptr;
    player = nullptr;
}


LuaHandler::~LuaHandler( void ) {
    Close();
}


void LuaHandler::Open( void ) {
    if ( L == nullptr ) {
        printf("LUA: Initializing new Lua State\n");
        L = luaL_newstate();
        luaL_openlibs( L );
    }
}


void LuaHandler::Close() {
    if (!L) {
        return;
    }
    printf("LUA: Shutting down Lua State\n");
    lua_close( L );
    L = nullptr;
}


Game* LuaHandler::GetGame() {
    if ( game == nullptr ) {
        printf("WARNING! Game object is null!\n");
    }
    return game;
}


void LuaHandler::RegisterObjects() {
    // before proceeding Lua script

    LUA::Parser::PlayerParser::RegisterObject(L);
    LUA::Parser::LevelParser::RegisterObject(L);
    LUA::Parser::GameParser::RegisterObject(L);

}


void LuaHandler::RetrieveObjects() {
    // after proceeding Lua script

    LUA::Object::Game tempGame = *LUA::Parser::GameParser::GetGame(L, "game");
    game = new LUA::Object::Game(tempGame);

    LUA::Object::Player tempPlayer = *LUA::Parser::PlayerParser::GetPlayer(L, "player");
    player = new LUA::Object::Player(tempPlayer);

    //printf("LUA: Player name=%s\n", player->name.c_str());

    //player->Move( L );

    //int result = LUA::Parser::PlayerParser::MovePlayer(L);
    //printf("LuaHandler result = %i\n", result);

    //player->Draw();

    //int (LUA::Object::Player:: * pt2Member)(float, char, char) = NULL;
    //(player->*Move)();

    //printf("LuaHandler: game name=%s, game->level name=%s, windowWidth=%i, windowHeight=%i\n", game->name.c_str(), game->level->name.c_str(), game->windowWidth, game->windowHeight);

    printf( "LUA: Memory used: %ikb\n", lua_gc(L, LUA_GCCOUNT, 0) );
}


bool LuaHandler::RunScript(const std::string fileName) {
    if ( L == nullptr ) {
        Open();
    }
    std::string fn = DIR_RES_SCRIPTS + fileName;
    printf("LUA: Running script: '%s'\n", fileName.c_str());
    if (fn.length() > 0) {
        RegisterObjects();
        if ( luaL_dofile( L, fn.c_str()) != LUA_OK ) {
            printf("LUA: Error while luaL_dofile script file ('%s'): %s\n", fileName.c_str(), lua_tostring( L, -1));
            return false;
        }
        RetrieveObjects();
        return true;
    }
    printf("LUA: Error while reading script file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1));
    return false;
}

bool LuaHandler::LoadLuaMap(const std::string fileName) {
    if (L == nullptr) {
        Open();
    }
    std::string fn = DIR_RES_SCRIPTS + fileName;
    printf("LUA: Loading map: '%s'\n", fileName.c_str());
    if (fn.length() > 0) {
        RegisterMapObject();
        if (luaL_dofile(L, fn.c_str()) != LUA_OK) {
            printf("LUA: Error while luaL_dofile map file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1));
            return false;
        }
        RetrieveMapObject();
        return true;
    }
    printf("LUA: Error while reading map file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1));
    return false;
}


void LuaHandler::RegisterMapObject() {

}

void LuaHandler::RetrieveMapObject() {
    
    if (lua_istable(L, 1)) {

        //Parser::Parser::TestStack(L);

        int topStack = lua_gettop(L);

        //lua_getfield(L, topStack, "version");
        //const char* version = lua_tostring(L, -1);
        std::string ver = TableGetString(L, topStack, "version");
        printf("Map version=%s\n", ver.c_str());

        int mapWidth = TableGetInt(L, topStack, "width");
        printf("Map width=%i\n", mapWidth);

        int mapHeight = TableGetInt(L, topStack, "height");
        printf("Map height=%i\n", mapHeight);

        int tilewidth = TableGetInt(L, topStack, "tilewidth");
        printf("Map tilewidth=%i\n", tilewidth);

        int tileHeight = TableGetInt(L, topStack, "tileheight");
        printf("Map tileHeight=%i\n", tileHeight);

        int nextlayerid = TableGetInt(L, topStack, "nextlayerid");
        printf("Map nextlayerid=%i\n", nextlayerid);

        int nextobjectid = TableGetInt(L, topStack, "nextobjectid");
        printf("Map nextobjectid=%i\n", nextobjectid);
        

        //lua_getfield(L, -6, "orientation");
        //const char* orientation = lua_tostring(L, -1);
        //printf("Map orientation=%s\n", orientation);

    }
    else {
        printf("LUA: map script was not loaded properly!\n");
    }


    //Parser::Parser::TestStack(L);

}

std::string LUA::LuaHandler::TableGetString(lua_State* _L, int _topStack, const char* _fieldName) {
    lua_getfield(_L, _topStack, _fieldName);
    if (lua_isstring(L, -1)) {
        const char* version = lua_tostring(_L, -1);
        return std::string(version);
    }
    return std::string();
}

int LUA::LuaHandler::TableGetInt(lua_State* _L, int _topStack, const char* _fieldName) {
    lua_getfield(_L, _topStack, _fieldName);
    if (lua_isinteger(L, -1)) {
        return (int)lua_tointeger(L, -1);
    }
    return 0;
}

