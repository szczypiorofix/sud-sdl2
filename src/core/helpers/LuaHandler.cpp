#include "LuaHandler.h"
#include "../Defines.h"



LuaHandler::LuaHandler() {
    L = nullptr;
    loadedScriptsIndex = 0;
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
    printf("LUA: Shutting down cuurent Lua State\n");
    if ( !L )
        return;
    lua_close( L );
    L = nullptr;
}


int LuaHandler::myobject_new( lua_State* L ) {
    double x = luaL_checknumber( L, 1 );
    *reinterpret_cast< TestModel** >( lua_newuserdata( L, sizeof( TestModel* ) ) ) = new TestModel( x );
    luaL_setmetatable( L, LUA_MYOBJECT );
    return 1;
}


void LuaHandler::RegisterObject() {
    lua_register( L, LUA_MYOBJECT, LuaHandler::myobject_new );
    luaL_newmetatable( L, LUA_MYOBJECT );
    lua_pushcfunction( L, myobject_delete ); lua_setfield( L, -2, "__gc" );
    lua_pushvalue( L, -1 ); lua_setfield( L, -2, "__index" );
    lua_pushcfunction( L, myobject_set ); lua_setfield( L, -2, "set" );
    lua_pushcfunction( L, myobject_get ); lua_setfield( L, -2, "get" );
    lua_pop( L, 1 );
}

int LuaHandler::myobject_delete(lua_State * L) {
    delete* reinterpret_cast< TestModel** >( lua_touserdata( L, 1 ) );
    return 0;
}

// MyObject member functions in Lua
int LuaHandler::myobject_set(lua_State * L) {
    ( *reinterpret_cast< TestModel** >( luaL_checkudata( L, 1, LUA_MYOBJECT ) ) )->set( luaL_checknumber( L, 2 ) );
    return 0;
}

int LuaHandler::myobject_get( lua_State* L ) {
    lua_pushnumber( L, ( *reinterpret_cast< TestModel** >( luaL_checkudata( L, 1, LUA_MYOBJECT ) ) )->get() );
    return 1;
}




struct Sprite {
    int x;
    int y;
    void Move(int velX, int velY) {
        x += velX;
        y += velY;
    }
};

auto CreateSprite = [](lua_State* L) -> int {
    Sprite* sprite = (Sprite*)lua_newuserdata(L, sizeof(Sprite));
    sprite->x = 0;
    sprite->y = 0;
    return 1;
};

auto MoveSprite = [](lua_State* L) -> int {
    Sprite* sprite = (Sprite*)lua_touserdata( L, -3 );
    lua_Number velX = lua_tonumber( L, -2 );
    lua_Number velY = lua_tonumber( L, -1 );
    sprite->Move(velX, velY);
    return 0;
};

void LuaHandler::BeforeRunningScript() {
    // before proceeding Lua script
    //RegisterObject();
    

    lua_pushcfunction( L, CreateSprite );
    lua_setglobal( L, "CreateSprite" );
    lua_pushcfunction(L, MoveSprite);
    lua_setglobal(L, "MoveSprite");


}


void LuaHandler::AfterRunningScript() {
    // after proceeding Lua script

    //printf("LUA: GC - memory reserved: %ikb\n", lua_gc(L, LUA_GCCOUNT, 0) );
    //printf("LUA: Stack length: %i\n", lua_gettop(L));
    //int maxStackSize = 24;
    //printf("LUA: checkStack for %i elements: %i\n", maxStackSize, lua_checkstack( L, maxStackSize ) );



    lua_getglobal(L, "sprite");
    if (lua_isuserdata(L, -1)) {
        Sprite* sprite = (Sprite*)lua_touserdata(L, -1);
        printf("LUA: Sprite x=%i, y=%i\n", sprite->x, sprite->y);
    }
    else {
        printf("LUA: Userdata of type 'Sprite' not found!\n");
    }
    
    printf("LUA: Memory reserved: %ikb\n", lua_gc(L, LUA_GCCOUNT, 0));
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
