#include "LuaHandler.h"
#include "../core/Defines.h"
#include "parsers/PlayerParser.h"
#include "parsers/LevelParser.h"
#include "parsers/GameParser.h"
#include "parsers/TestParser.h"



LuaHandler::LuaHandler() {
    L = nullptr;
    game = nullptr;
    player = nullptr;
    tiledMap = nullptr;
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
    
    if (game != nullptr) {
        delete game->level; // delete LuaLevel object first
        delete game;        // then delete LuaGame object
    }
    
    if (player != nullptr) {
        delete player;
    }
    
    if (tiledMap != nullptr) {
        delete tiledMap;
    }
    

    printf("LUA: Shutting down Lua State\n");
    lua_close( L );
    L = nullptr;
}


LuaGame* LuaHandler::GetGame() {
    if ( game == nullptr ) {
        printf("WARNING! Game object is null!\n");
    }
    return game;
}

TiledMap* LuaHandler::GetTiledMap() {
    return tiledMap;
}


void LuaHandler::RegisterObjects() {
    // before proceeding Lua script

    PlayerParser::RegisterObject(L);
    LevelParser::RegisterObject(L);
    GameParser::RegisterObject(L);

}


void LuaHandler::RetrieveObjects() {
    // after proceeding Lua script

    LuaGame tempGame = *GameParser::GetGame(L, "game");
    game = new LuaGame(tempGame);

    LuaPlayer tempPlayer = *PlayerParser::GetPlayer(L, "player");
    player = new LuaPlayer(tempPlayer);

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
        //if (tiledMap != nullptr) {
        //    delete tiledMap;
        //}
        tiledMap = new TiledMap(fn, L);
        return true;
    }
    printf("LUA: Error while reading map file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1));
    return false;
}


bool LuaHandler::RunTestScript(const std::string fileName) {
    if (L == nullptr) {
        Open();
    }
    std::string fn = DIR_RES_SCRIPTS + fileName;
    printf("LUA: Running test script: '%s'\n", fileName.c_str());
    if (fn.length() > 0) {
        RegisterTestObjects();
        if (luaL_dofile(L, fn.c_str()) != LUA_OK) {
            printf("LUA: Error while luaL_dofile script file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1));
            return false;
        }
        RetrieveTestObject();
        return true;
    }
    printf("LUA: Error while reading script file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1));
    return false;
}


void LuaHandler::RegisterTestObjects() {
    TestParser::RegisterObject(L);
}


void LuaHandler::RetrieveTestObject() {
    TestParser::ResolveObjects(L);
}
