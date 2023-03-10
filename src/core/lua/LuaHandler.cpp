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


void LuaHandler::BeforeRunningScript() {
    // before proceeding Lua script

    LUA::Parser::PlayerParser::RegisterObject(L);
    LUA::Parser::LevelParser::RegisterObject(L);
    LUA::Parser::GameParser::RegisterObject(L);
}


void LuaHandler::AfterRunningScript() {
    // after proceeding Lua script

    LUA::Object::Game tempGame = *LUA::Parser::GameParser::GetGame(L, "game");
    game = new LUA::Object::Game(tempGame);

    LUA::Object::Player tempPlayer = *LUA::Parser::PlayerParser::GetPlayer(L, "player");
    player = new LUA::Object::Player(tempPlayer);

    //printf("LUA: Player name=%s\n", player->name.c_str());

    int podx = 0; // player->OnDraw(L);

    printf("LuaHandler: game name=%s, game->level name=%s, podx=%i\n", tempGame.name.c_str(), tempGame.level->name.c_str(), podx);

    printf( "LUA: Memory used: %ikb\n", lua_gc(L, LUA_GCCOUNT, 0) );

}



bool LuaHandler::RunScript(const std::string fileName) {
    if ( L == nullptr ) {
        Open();
    }
    std::string fn = DIR_RES_SCRIPTS + fileName;
    printf("LUA: Running script: '%s'\n", fileName.c_str());
    if (fn.length() > 0) {
        BeforeRunningScript();
        if ( luaL_dofile( L, fn.c_str()) != LUA_OK ) {
            printf("LUA: Error while luaL_dofile script file ('%s'): %s\n", fileName.c_str(), lua_tostring( L, -1));
            return false;
        }
        AfterRunningScript();
        return true;
    }
    printf("LUA: Error while reading script file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1));
    return false;
}


bool LuaHandler::ProcessText(const char* content) {
    if (L == nullptr) {
        Open();
    }
    return luaL_dostring(L, content) == 0;
}


bool LuaHandler::GetGlobal(const char* name) {
    return lua_getglobal(this->L, name) != 0;
}


bool LuaHandler::GetInt(const char*variableName, int& value) {    
    if (!GetGlobal(variableName)) {
        printf("LUA: Cannot find variable: %s\n", variableName);
        return false;
    }

    if (lua_isnumber(L, -1) == false) {
        lua_pop(L, 1);
        return false;
    }
    value = (int)(lua_tointeger(L, -1));
    lua_pop(L, 1);

    return true;
}

bool LuaHandler::GetFunctionStringTuple( const char* functionName, std::vector<std::string>& returnValues, const int returnValuesCounter ) {
    Open();
    lua_getglobal( L, functionName );
    if ( lua_isfunction( L, -1 ) ) {
        lua_pcall( L, 0, returnValuesCounter, 0); // Lua Statem, 0 function parameters, 1 parameter in return, 0 - error handling
        for ( int i = 0; i < returnValuesCounter; i++ ) {
            returnValues.push_back( lua_tostring( L, (i + 1) * -1) );
            std::reverse( returnValues.begin(), returnValues.end());
        }
    }
    return false;
}


bool LuaHandler::GetFunctionIntValue( const char* functionName, int& value ) {
    Open();
    lua_getglobal( L, functionName );
    if ( lua_isfunction( L, -1 ) ) {
        lua_pcall( L, 0, 1, 0 ); // Lua Statem, 0 function parameters, 1 parameter in return, 0 - error handling
        lua_Number luaValue = lua_tonumber( L, -1 );
        value = ( int ) luaValue;
    }
    return false;
}
