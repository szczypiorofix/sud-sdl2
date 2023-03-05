#include "LuaHandler.h"
#include "../Defines.h"




LuaHandler::LuaHandler() {
    L = nullptr;
    loadedScriptsIndex = 0;
    game = nullptr;
    level = nullptr;
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
    //game = new LuaGen::Game("game");
    //level = new LuaGen::Level();
}


void LuaHandler::Close() {
    printf("LUA: Shutting down Lua State\n");
    if (!L) {
        return;
    }
    lua_close( L );
    L = nullptr;
}


LuaGen::Game* LuaHandler::GetGame() {
    if (game == nullptr) {
        printf("WARNING! Game object is null!\n");
    }
    return game;
}

LuaGen::Level* LuaHandler::GetLevel() {
    if (level == nullptr) {
        printf("WARNING! Level object is null!\n");
    }
    return level;
}


void LuaHandler::BeforeRunningScript() {
    // before proceeding Lua script
    //RegisterObject();
    
    //LuaObjectParser::RegisterSpriteObject( L );

    LuaObjectParser::RegisterGameObject( L );

}


void LuaHandler::AfterRunningScript() {
    // after proceeding Lua script

    //Level* level01 = LuaObjectParser::GetLevel(L, "level01");

    //Sprite* sprite = LuaObjectParser::GetSprite(L, "sprite2");
    //if (sprite) {
    //    printf("Getting Sprite object from Lua: address=%p name=%s, x=%i, y=%i\n", &sprite, sprite->name.c_str(), sprite->x, sprite->y);
    //}

    //game = LuaObjectParser::GetGame(L, "game");
    //level = LuaObjectParser::GetLevel(L, "level");
    //printf("Level name=%s, content=%s\n", level->name, level->content);




    game = LuaObjectParser::GetGame(L, "game");


    //level = new LuaGen::Level( *(LuaObjectParser::GetLevel(L, "level")) );
    //level = new LuaGen::Level("nn", 12, 16, "-content-");

    //printf("LuaHandler level name=%s\n", level->name.c_str());
    //printf("LuaHandler level width=%i\n", level->width);
    //printf("LuaHandler level height=%i\n", level->height);
    //printf("LuaHandler level content=%s\n", level->content.c_str());

    //printf("LuaHandler game name=%s\n", game->name);
    //printf("LuaHandler game level name=%s\n", game->level->content);


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


bool LuaHandler::LoadScript( const std::string fileName ) {
    if ( L == nullptr ) {
        Open();
    }
    std::string fn = DIR_RES_SCRIPTS + fileName;
    printf( "LUA: Loading script '%s'\n", fileName.c_str() );
    if (fn.length() > 0 ) {
        if ( luaL_loadfile( L, fn.c_str() ) != LUA_OK ) {
            printf( "LUA: Error while luaL_dofile script file ('%s'): %s\n", fileName.c_str(), lua_tostring( L, -1 ) );
            return false;
        }
        loadedScriptsIndex++;
        return true;
    }
    printf("LUA: Error while reading script file ('%s'): %s\n", fileName.c_str(), lua_tostring(L, -1) );
    return false;
}


bool LuaHandler::RunLoadedScripts() {
    if (L == nullptr) {
        printf("LUA: Error! Lua state object is null! \n");
        return false;
    }

    // No, it's not working ... :(
    //for ( int i = 0; i < loadedScriptsIndex; i++ ) {
    //    if ( lua_pcall(L, 0, 0, 0) != LUA_OK ) {
    //        return false;
    //    }
    //    lua_pop( L, 1 );
    //}

    //if ( lua_pcall( L, 0, 0, 0 ) == LUA_OK ) {
    //    printf( "LUA: Run all loaded Lua chunks. \n" );
    //    return true;
    //}
    printf("LUA: Error! Loaded Lua chunks cannot be processed: %s\n", lua_tostring(L, -1) );
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
