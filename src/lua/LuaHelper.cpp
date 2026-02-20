#include "LuaHelper.h"
#include <iostream>



std::string LuaHelper::TableGetString(lua_State* _L, const char* _fieldName, int _topStack) {
    lua_getfield(_L, _topStack, _fieldName);
    if (lua_isstring(_L, -1)) {
        std::string result = lua_tostring(_L, -1);
        lua_pop(_L, 1);
        return result;
    }
    printf("LUA: LuaHelper:TableGetString - warning! Wrong data type for '%s'. Should be 'string', got '%s'\n", _fieldName, lua_typename(_L, lua_type(_L, -1)));
    lua_remove(_L, -1);
    return std::string("");
}


int LuaHelper::TableGetInt(lua_State* _L, const char* _fieldName, int _topStack) {
    lua_getfield(_L, _topStack, _fieldName);
    if (lua_isinteger(_L, -1)) {
        int r = (int)lua_tointeger(_L, -1);
        lua_remove(_L, -1);
        return r;
    }
    printf("LUA: LuaHelper:TableGetInt - warning! Wrong data type for '%s'. Should be 'int', got '%s'\n", _fieldName, lua_typename(_L, lua_type(_L, -1)));
    lua_remove(_L, -1);
    return 0;
}


bool LuaHelper::TableGetBool(lua_State* _L, const char* _fieldName, int _topStack) {
    lua_getfield(_L, _topStack, _fieldName);
    if (lua_isboolean(_L, -1)) {
        bool r = lua_toboolean(_L, -1);
        lua_remove(_L, -1);
        return r;
    }
    printf("LUA: LuaHelper:TableGetBool - warning! Wrong data type for '%s'. Should be 'bool', got '%s'\n", _fieldName, lua_typename(_L, lua_type(_L, -1)));
    lua_remove(_L, -1);
    return false;
}


float LuaHelper::TableGetFloat(lua_State* _L, const char* _fieldName, int _topStack) {
    lua_getfield(_L, _topStack, _fieldName);
    if (lua_isnumber(_L, -1)) {
        float r = (float)lua_tonumber(_L, -1);
        lua_remove(_L, -1);
        return r;
    }
    printf("LUA: LuaHelper:TableGetFloat - warning! Wrong data type for '%s'. Should be 'float', got '%s'\n", _fieldName, lua_typename(_L, lua_type(_L, -1)));
    lua_remove(_L, -1);
    return 0.0f;
}

void LuaHelper::TestStack(lua_State* L) {
    std::cout << "LUA: Test stack (size=" << lua_gettop(L) << ")" << std::endl;
    int stack = lua_gettop(L);
    for (int i = 1; i <= stack; i++) {
        std::cout << std::dec << i << ": " << lua_typename(L, lua_type(L, i));
        switch (lua_type(L, i)) {
        case LUA_TBOOLEAN:
            std::cout << " " << lua_toboolean(L, i);
            break;
        case LUA_TFUNCTION:
            std::cout << " " << std::hex << lua_topointer(L, i);
            break;
        case LUA_TSTRING:
            std::cout << " " << lua_tostring(L, i);
            break;
        case LUA_TNUMBER:
            std::cout << " " << std::dec << (uintptr_t)lua_tointeger(L, i) << " (0x" << std::hex << lua_tointeger(L, i) << ")";
            break;
        default:
            std::cout << " " << std::hex << lua_topointer(L, i);
            break;
        }
        std::cout << std::endl;
    }
}

