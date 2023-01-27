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
        //SetLuaPath(luaState, "res\scripts");
    }
}


void LuaHandler::Close() {
    printf("LUA: Shutting down Lua State\n");
    if (!luaState)
        return;
    lua_close(luaState);
    luaState = nullptr;
}


bool LuaHandler::LoadFile(const std::string fileName) {
    if (luaState == nullptr) {
        Open();
    }
    std::string fn = DIR_RES_SCRIPTS + fileName;
    if (fn.length() > 0 ) {
        luaL_loadfile(luaState, fn.c_str());
        if (lua_pcall(luaState, 0, 0, 0) == LUA_OK) {
            return true;
        }
    }
    printf("Lua error while reading script file (%s): %s\n", fileName.c_str(), lua_tostring(luaState, -1) );
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
        printf("Cannot find variable: %s\n", variableName);
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

