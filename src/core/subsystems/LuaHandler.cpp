#include "LuaHandler.h"
#include "../Defines.h"



LuaHandler::LuaHandler() {
    luaState = nullptr;
}


LuaHandler::~LuaHandler( void ) {
    Close();
}


void LuaHandler::Open( void ) {
    if ( luaState == nullptr ) {
        printf("LUA: Initializing new Lua State\n");
        luaState = luaL_newstate();
        luaL_openlibs( luaState );
    }
}


void LuaHandler::Close() {
    printf("LUA: Shutting down Lua State\n");
    if (!luaState)
        return;
    lua_close(luaState);
    luaState = nullptr;
}


int LuaHandler::myobject_new( lua_State* L ) {
    double x = luaL_checknumber( L, 1 );
    *reinterpret_cast< TestModel** >( lua_newuserdata( L, sizeof( TestModel* ) ) ) = new TestModel( x );
    luaL_setmetatable( L, LUA_MYOBJECT );
    return 1;
}


void LuaHandler::RegisterObject() {
    lua_register( luaState, LUA_MYOBJECT, LuaHandler::myobject_new );
    luaL_newmetatable( luaState, LUA_MYOBJECT );
    lua_pushcfunction( luaState, myobject_delete ); lua_setfield( luaState, -2, "__gc" );
    lua_pushvalue( luaState, -1 ); lua_setfield( luaState, -2, "__index" );
    lua_pushcfunction( luaState, myobject_set ); lua_setfield( luaState, -2, "set" );
    lua_pushcfunction( luaState, myobject_get ); lua_setfield( luaState, -2, "get" );
    //lua_pop( luaState, 1 );
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


bool LuaHandler::LoadFile(const std::string fileName) {
    if (luaState == nullptr) {
        Open();
    }
    std::string fn = DIR_RES_SCRIPTS + fileName;
    printf( "LUA: Loading file '%s'\n", fileName.c_str() );
    if (fn.length() > 0 ) {
        
        RegisterObject();

        // luaL_dofile or luaL_loadfile ??
        if ( luaL_dofile( luaState, fn.c_str() ) != LUA_OK ) {
            printf( "LUA: Error while luaL_dofile script file ('%s'): %s\n", fileName.c_str(), lua_tostring( luaState, -1 ) );
            return false;
        }

        return true;
        
        /*if (lua_pcall(luaState, 0, 0, 0) == LUA_OK) {
            printf( "LUA: Script file '%s' loaded. \n", fileName.c_str() );
            return true;
        }*/
    }
    printf("LUA: Error while reading script file ('%s'): %s\n", fileName.c_str(), lua_tostring(luaState, -1) );
    return false;
}


bool LuaHandler::ProcessText(const char* content) {
    if (luaState == nullptr) {
        Open();
    }
    return luaL_dostring(luaState, content) == 0;
}


bool LuaHandler::GetGlobal(const char* name) {
    return lua_getglobal(this->luaState, name) != 0;
}


bool LuaHandler::GetInt(const char*variableName, int& value) {    
    if (!GetGlobal(variableName)) {
        printf("LUA: Cannot find variable: %s\n", variableName);
        return false;
    }

    if (lua_isnumber(luaState, -1) == false) {
        lua_pop(luaState, 1);
        return false;
    }
    value = (int)(lua_tointeger(luaState, -1));
    lua_pop(luaState, 1);

    return true;
}

bool LuaHandler::GetFunctionStringTuple( const char* functionName, std::vector<std::string>& returnValues, const int returnValuesCounter ) {
    Open();
    lua_getglobal( luaState, functionName );
    if ( lua_isfunction( luaState, -1 ) ) {
        lua_pcall( luaState, 0, returnValuesCounter, 0); // Lua Statem, 0 function parameters, 1 parameter in return, 0 - error handling
        for ( int i = 0; i < returnValuesCounter; i++ ) {
            returnValues.push_back( lua_tostring( luaState, (i + 1) * -1) );
            std::reverse( returnValues.begin(), returnValues.end());
        }
    }
    return false;
}


bool LuaHandler::GetFunctionIntValue( const char* functionName, int& value ) {
    Open();
    lua_getglobal( luaState, functionName );
    if ( lua_isfunction( luaState, -1 ) ) {
        lua_pcall( luaState, 0, 1, 0 ); // Lua Statem, 0 function parameters, 1 parameter in return, 0 - error handling
        lua_Number luaValue = lua_tonumber( luaState, -1 );
        value = ( int ) luaValue;
    }
    return false;
}
