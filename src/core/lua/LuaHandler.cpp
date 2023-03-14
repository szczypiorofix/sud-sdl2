#include "LuaHandler.h"
#include "../Defines.h"
#include "parsers/PlayerParser.h"
#include "parsers/LevelParser.h"
#include "parsers/GameParser.h"



using namespace LUA;

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


LUA::Object::Game* LuaHandler::GetGame() {
    if ( game == nullptr ) {
        printf("WARNING! Game object is null!\n");
    }
    return game;
}


void LuaHandler::InitializeObjects() {
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
        InitializeObjects();
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

