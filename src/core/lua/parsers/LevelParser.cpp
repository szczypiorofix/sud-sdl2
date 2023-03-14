#include "LevelParser.h"
#include <sstream>
#include <assert.h>


using namespace LUA::Parser;
using namespace LUA::Object;


void LevelParser::RegisterObject(lua_State* L) {

    // New table
    lua_newtable(L);
    // Level table index on Lua stack 
    int levelTableIdx = lua_gettop(L);
    lua_pushvalue(L, levelTableIdx);
    lua_setglobal(L, "Level");

    // Level contructor
    lua_pushcfunction(L, LevelParser::_new);
    lua_setfield(L, -2, "new");

    // ============== metamethods =====================
    // Creating new metatable
    luaL_newmetatable(L, "LevelMetaTable");

    lua_pushstring(L, "__gc"); // Garbage Collector metamethod - runs Level destructor
    lua_pushcfunction(L, LevelParser::_destroy);
    lua_settable(L, -3);

    lua_pushstring(L, "__tostring"); // tostring metamethod override
    lua_pushcfunction(L, LevelParser::_tostring);
    lua_settable(L, -3);

    lua_pushstring(L, "__index"); // seting the proper index for LevelMetaTable
    lua_pushcfunction(L, LevelParser::_index);
    lua_settable(L, -3);

    lua_pushstring(L, "__newindex"); // seting the proper new index for LevelMetaTable
    lua_pushcfunction(L, LevelParser::_newindex);
    lua_settable(L, -3);
}

int LevelParser::_new(lua_State* L) {

    //printf("Level: constructor\n");

    void* pointerToLevel = lua_newuserdata(L, sizeof(Level));
    Level* level = new (pointerToLevel) Level();

    int tableId = 0;

    if (lua_istable(L, 2)) {
        tableId = 2; // constructor parameter is table!
    }

    luaL_getmetatable(L, "LevelMetaTable");
    assert(lua_istable(L, -1)); // check if last lua stack item - metatable - is a table

    if (tableId > 0 && lua_istable(L, tableId)) {
        lua_setmetatable(L, 3);
    }
    else {
        lua_setmetatable(L, 2);

        lua_newtable(L);
        lua_setuservalue(L, 1);
    }

    // Get contructor parameters ...
    if (tableId > 0 && lua_istable(L, tableId)) {
        //printf("Level: constructor - parameter is a table!\n");
        lua_getfield(L, tableId, "name");
        const char* pName = lua_tostring(L, -1);
        //printf("Level: constructor - set parameter 'name' to %s\n", pName);
        level->name = pName;

        lua_getfield(L, tableId, "width");
        lua_Number pWidth = lua_tonumber(L, -1);
        //printf("Level: constructor - set parameter 'width' to %i\n", (int)pWidth);
        level->width = (uint32_t)pWidth;

        lua_getfield(L, tableId, "height");
        lua_Number pHeight = lua_tonumber(L, -1);
        //printf("Level: constructor - set parameter 'height' to %i\n", (int)pHeight);
        level->height = (uint32_t)pHeight;

        lua_getfield(L, tableId, "background");
        const char* pBackground = lua_tostring(L, -1);
        //printf("Level: constructor - set parameter 'background' to %s\n", pBackground);
        level->background = pBackground;

        lua_getfield(L, tableId, "foreground");
        const char* pForeground = lua_tostring(L, -1);
        //printf("Level: constructor - set parameter 'foreground' to %s\n", pForeground);
        level->foreground = pForeground;

        lua_settop(L, 3);
    }

    return 1;
}

int LevelParser::_destroy(lua_State* L) {
    Level* level = (Level*)lua_touserdata(L, -1);
    level->~Level();
    //printf("Level: destroy\n");
    return 0;
}

int LevelParser::_tostring(lua_State* L) {
    Level* level = (Level*)lua_touserdata(L, -1);
    std::stringstream ss;
    ss << "Level.__tostring memaddr=" << (void const*)level << ", name=" << level->name << ", width=" << level->width << ", height=" << level->height << ", background=" << level->background << ", foreground=" << level->foreground;
    std::string s = ss.str();
    lua_pushstring(L, s.c_str());
    return 1;
}

int LevelParser::_index(lua_State* L) {
    assert(lua_isuserdata(L, -2));
    assert(lua_isstring(L, -1));

    Level* level = (Level*)lua_touserdata(L, -2);
    const char* index = lua_tostring(L, -1);

    if (strcmp(index, "name") == 0) {
        //printf("(GET)Level->name\n");
        lua_pushstring(L, level->name.c_str());
        return 1;
    }
    else if (strcmp(index, "width") == 0) {
        //printf("(GET)Level->width\n");
        lua_pushnumber(L, level->width);
        return 1;
    }
    else if (strcmp(index, "height") == 0) {
        //printf("(GET)Level->height\n");
        lua_pushnumber(L, level->height);
        return 1;
    }
    else if (strcmp(index, "background") == 0) {
        //printf("(GET)Level->background\n");
        lua_pushstring(L, level->background.c_str());
        return 1;
    }
    else if (strcmp(index, "foreground") == 0) {
        //printf("(GET)Level->foreground\n");
        lua_pushstring(L, level->foreground.c_str());
        return 1;
    }
    else {
        lua_getglobal(L, "Level");
        lua_pushstring(L, index);
        lua_rawget(L, -2);
        return 1;
    }
}

int LevelParser::_newindex(lua_State* L) {
    assert(lua_isuserdata(L, -3)); // 1
    assert(lua_isstring(L, -2));   // 2
    // -1 a value we want to set   // 3

    Level* level = (Level*)lua_touserdata(L, -3);
    const char* index = lua_tostring(L, -2);

    if (strcmp(index, "name") == 0) {
        if (lua_isstring(L, -1)) {
            const char* name = lua_tostring(L, -1);
            //printf("Level: set 'name' to %s\n", name);
            level->name = name;
        }
        else {
            printf("Level: trying set 'name' to wrong data type! Got %s, string required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else if (strcmp(index, "width") == 0) {
        if (lua_isnumber(L, -1)) {
            lua_Number width = lua_tonumber(L, -1);
            //printf("Level: set 'width' to %i\n", (int)width);
            level->width = (uint32_t)width;
        }
        else {
            printf("Level: trying set 'width' to wrong data type! Got %s, number required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else if (strcmp(index, "height") == 0) {
        if (lua_isnumber(L, -1)) {
            lua_Number height = lua_tonumber(L, -1);
            //printf("Level: set 'height' to %i\n", (int)height);
            level->height = (uint32_t)height;
        }
        else {
            printf("Level: trying set 'height' to wrong data type! Got %s, number required.\n", lua_typename(L, lua_type(L, -1)));
        }

    }
    else if (strcmp(index, "background") == 0) {
        if (lua_isstring(L, -1)) {
            const char* background = lua_tostring(L, -1);
            //printf("Level: set 'background' to %s\n", background);
            level->background = background;
        }
        else {
            printf("Level: trying set 'background' to wrong data type! Got %s, string required.\n", lua_typename(L, lua_type(L, -1)));
        }

    }
    else if (strcmp(index, "foreground") == 0) {
        if (lua_isstring(L, -1)) {
            const char* foreground = lua_tostring(L, -1);
            //printf("Level: set 'foreground' to %s\n", foreground);
            level->foreground = foreground;
        }
        else {
            printf("Level: trying set 'foreground' to wrong data type! Got %s, string required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else {
        printf("Level: user trying to add an object of type '%s' to an unknown field '%s'\n", lua_typename(L, lua_type(L, -1)), index);

        //lua_getuservalue(L, 1); // 1
        //lua_pushvalue(L, 2);    // 2
        //lua_pushvalue(L, 3);    // 3
        //lua_settable(L, -3);    // 1[2] = 3

    }
    return 0;
}

Level* LevelParser::GetLevel(lua_State* L, const char* objectName) {
    lua_getglobal(L, objectName);
    if (lua_isuserdata(L, -1)) {
        Level* level = (Level*)lua_touserdata(L, -1);
        //printf("Returning level : %s\n", level->name.c_str());
        return level;
    }
    printf("Object %s (Level) not found !!!\n", objectName);
    return nullptr;
}

