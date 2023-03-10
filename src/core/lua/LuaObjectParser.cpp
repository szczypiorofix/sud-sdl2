#include "LuaObjectParser.h"

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include "generic/Level.h"



void LuaObjectParser::TestStack(lua_State* L) {
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



// ============== PLAYER ====================

void LuaObjectParser::RegisterPlayerObject(lua_State* L) {

    // New table
    lua_newtable(L);
    // Game table index on Lua stack 
    int gameTableIdx = lua_gettop(L);
    lua_pushvalue(L, gameTableIdx);
    lua_setglobal(L, "Player");

    // Game contructor
    lua_pushcfunction(L, LuaObjectParser::_newPlayer);
    lua_setfield(L, -2, "new");

    // Creating new metatable
    luaL_newmetatable(L, "PlayerMetaTable");

    lua_pushstring(L, "__gc"); // Garbage Collector metamethod - runs Player destructor
    lua_pushcfunction(L, LuaObjectParser::_destroyPlayer);
    lua_settable(L, -3);

    //lua_pushstring(L, "__tostring"); // tostring metamethod override
    //lua_pushcfunction(L, LuaObjectParser::_tostringPlayer);
    //lua_settable(L, -3);

    lua_pushstring(L, "__index"); // seting the proper index for PlayerMetaTable
    lua_pushcfunction(L, LuaObjectParser::_indexPlayer);
    lua_settable(L, -3);

    lua_pushstring(L, "__newindex"); // seting the proper new index for PlayerMetaTable
    lua_pushcfunction(L, LuaObjectParser::_newindexPlayer);
    lua_settable(L, -3);
}

int LuaObjectParser::_newPlayer(lua_State* L) {
    return 1;
}

int LuaObjectParser::_destroyPlayer(lua_State* L) {
    using namespace LuaGen;
    Player* player = (Player*)lua_touserdata(L, -1);
    player->~Player();
    //printf("Player: destroy\n");
    return 0;
}

int LuaObjectParser::_indexPlayer(lua_State* L) {
    return 0;
}

int LuaObjectParser::_newindexPlayer(lua_State* L) {
    return 0;
}

LuaGen::Player* LuaObjectParser::GetPlayer(lua_State* L, const char* playerName) {
    return new LuaGen::Player();
}

// =========================================



// ============== LEVEL ====================

void LuaObjectParser::RegisterLevelObject(lua_State* L) {

    // New table
    lua_newtable(L);
    // Game table index on Lua stack 
    int gameTableIdx = lua_gettop(L);
    lua_pushvalue(L, gameTableIdx);
    lua_setglobal(L, "Level");

    // Game contructor
    lua_pushcfunction(L, LuaObjectParser::_newLevel);
    lua_setfield(L, -2, "new");

    // Creating new metatable
    luaL_newmetatable(L, "LevelMetaTable");

    lua_pushstring(L, "__gc"); // Garbage Collector metamethod - runs Level destructor
    lua_pushcfunction(L, LuaObjectParser::_destroyLevel);
    lua_settable(L, -3);

    lua_pushstring(L, "__tostring"); // tostring metamethod override
    lua_pushcfunction(L, LuaObjectParser::_tostringLevel);
    lua_settable(L, -3);

    lua_pushstring(L, "__index"); // seting the proper index for LevelMetaTable
    lua_pushcfunction(L, LuaObjectParser::_indexLevel);
    lua_settable(L, -3);

    lua_pushstring(L, "__newindex"); // seting the proper new index for LevelMetaTable
    lua_pushcfunction(L, LuaObjectParser::_newindexLevel);
    lua_settable(L, -3);
}

int LuaObjectParser::_newLevel(lua_State* L) {
    using namespace LuaGen;

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
        lua_remove(L, -1); // remove from stack after assign

        lua_getfield(L, tableId, "width");
        lua_Number pWidth = lua_tonumber(L, -1);
        //printf("Level: constructor - set parameter 'width' to %i\n", (int)pWidth);
        level->width = (uint32_t)pWidth;
        lua_remove(L, -1); // remove from stack after assign

        lua_getfield(L, tableId, "height");
        lua_Number pHeight = lua_tonumber(L, -1);
        //printf("Level: constructor - set parameter 'height' to %i\n", (int)pHeight);
        level->height = (uint32_t)pHeight;
        lua_remove(L, -1); // remove from stack after assign

        lua_getfield(L, tableId, "background");
        const char* pBackground = lua_tostring(L, -1);
        //printf("Level: constructor - set parameter 'background' to %s\n", pBackground);
        level->background = pBackground;
        lua_remove(L, -1); // remove from stack after assign

        lua_getfield(L, tableId, "foreground");
        const char* pForeground = lua_tostring(L, -1);
        //printf("Level: constructor - set parameter 'foreground' to %s\n", pForeground);
        level->foreground = pForeground;
        lua_remove(L, -1); // remove from stack after assign
    }

    //TestStack(L);
    return 1;
}

int LuaObjectParser::_destroyLevel(lua_State* L) {
    using namespace LuaGen;
    Level* level = (Level*)lua_touserdata(L, -1);
    level->~Level();
    //printf("Level: destroy\n");
    return 0;
}

int LuaObjectParser::_tostringLevel(lua_State* L) {
    using namespace LuaGen;
    Level* level = (Level*)lua_touserdata(L, -1);
    std::stringstream ss;
    ss << "Level.__tostring memaddr=" << (void const*)level << ", name=" << level->name << ", width=" << level->width << ", height=" << level->height << ", background=" << level->background << ", foreground=" << level->foreground;
    std::string s = ss.str();
    lua_pushstring(L, s.c_str());
    return 1;
}

int LuaObjectParser::_indexLevel(lua_State* L) {
    using namespace LuaGen;
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

int LuaObjectParser::_newindexLevel(lua_State* L) {
    using namespace LuaGen;
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
        printf("Level: user trying to add unknown field '%s' to the object\n", index);

        //lua_getuservalue(L, 1); // 1
        //lua_pushvalue(L, 2);    // 2
        //lua_pushvalue(L, 3);    // 3
        //lua_settable(L, -3);    // 1[2] = 3

        //TestStack(L);
    }
    return 0;
}

LuaGen::Level* LuaObjectParser::GetLevel(lua_State* L, const char* objectName) {
    lua_getglobal(L, objectName);
    if (lua_isuserdata(L, -1)) {
        LuaGen::Level* level = (LuaGen::Level*)lua_touserdata(L, -1);
        //printf("Returning level : %s\n", level->name.c_str());
        return level;
    }
    printf("Object %s (Level) not found !!!\n", objectName);
    return nullptr;
}

// ==========================================


// ================== GAME ==================

void LuaObjectParser::RegisterGameObject(lua_State* L) {

    LuaObjectParser::RegisterLevelObject(L);

    // New table
    lua_newtable(L);
    // Game table index on Lua stack 
    int gameTableIdx = lua_gettop(L);
    lua_pushvalue(L, gameTableIdx);
    lua_setglobal(L, "Game");

    // Game contructor
    lua_pushcfunction(L, LuaObjectParser::_newGame);
    lua_setfield(L, -2, "new");

    // Creating new metatable
    luaL_newmetatable(L, "GameMetaTable");

    lua_pushstring(L, "__gc"); // Garbage Collector metamethod - runs Game destructor
    lua_pushcfunction(L, LuaObjectParser::_destroyGame);
    lua_settable(L, -3);

    lua_pushstring(L, "__tostring"); // tostring metamethod override
    lua_pushcfunction(L, LuaObjectParser::_tostringGame);
    lua_settable(L, -3);

    lua_pushstring(L, "__concat"); // concatenation of string metamethod override
    lua_pushcfunction(L, LuaObjectParser::_concatstringGame);
    lua_settable(L, -3);

    lua_pushstring(L, "__index"); // seting the proper index for GameMetaTable
    lua_pushcfunction(L, LuaObjectParser::_indexGame);
    lua_settable(L, -3);

    lua_pushstring(L, "__newindex"); // seting the proper new index for GameMetaTable
    lua_pushcfunction(L, LuaObjectParser::_newindexGame);
    lua_settable(L, -3);
}


int LuaObjectParser::_newGame(lua_State* L) {
    using namespace LuaGen;

    //printf("Game: new\n");

    void* pointerToAGame = lua_newuserdata(L, sizeof(Game));
    Game* game = new (pointerToAGame) Game("default_game");
    game->level = new Level();

    // string parameter
    if (lua_isstring(L, -2)) {
        const char* gameName = lua_tostring(L, -2);
        //printf("Game: parameter 'name' set to '%s'\n", gameName);
        game->name = gameName;
    }

    //printf("A new game has been created (name=%s).\n", game->name);
    luaL_getmetatable(L, "GameMetaTable");
    assert(lua_istable(L, -1));
    lua_setmetatable(L, 3);

    //TestStack(L);

    // Stack:
    // 1 - table - metatable GameMetaTable
    // 2 - string - parameter (name)
    // 3 - userdata - game
    // 

    return 1;
};


int LuaObjectParser::_destroyGame(lua_State* L) {
    using namespace LuaGen;
    Game* game = (Game*)lua_touserdata(L, -1);
    game->~Game();
    //printf("Game: destroy\n");
    return 0;
};

// Getter
int LuaObjectParser::_indexGame(lua_State* L) {
    using namespace LuaGen;

    assert(lua_isuserdata(L, 1)); // userdata - 1 (game)
    assert(lua_isstring(L, 2));   // string   - 2 (parameter)
        

    Game* game = (Game*)lua_touserdata(L, 1);
    const char* index = lua_tostring(L, 2);

    if (strcmp(index, "name") == 0) {
        //printf("(GET)Game->name\n");
        lua_pushstring(L, game->name.c_str());
        return 1;
    }
    else if (strcmp(index, "level") == 0) {
        //printf("(GET)Game->level\n");

        void* levelPointer = lua_newuserdata(L, sizeof(Level));

        Level* tl = new(levelPointer) Level( *game->level );

        //printf("TempLevel %s\n", tl->name.c_str());


        luaL_getmetatable(L, "LevelMetaTable");
        assert(lua_istable(L, -1));
        lua_setmetatable(L, -2);

        //TestStack(L);

        return 1;
    } else {
        lua_getglobal(L, "Game");
        lua_pushstring(L, index);
        lua_rawget(L, -2);

        return 1;
    }
}

//Setter
int LuaObjectParser::_newindexGame(lua_State* L) {
    using namespace LuaGen;

    assert(lua_isuserdata(L, -3));
    assert(lua_isstring(L, -2));

    Game* game = (Game*)lua_touserdata(L, -3);
    const char* index = lua_tostring(L, -2);

    if (strcmp(index, "name") == 0) {
        if (lua_isstring(L, -1)) {
            const char* name = lua_tostring(L, -1);
            //printf("Game: set 'name' to %s\n", name);
            game->name = name;
        }
        else {
            printf("Game: trying set 'level' to wrong data type! Got %s, string required.\n", lua_typename(L, lua_type(L, -1)));
        }
        
    }
    else if (strcmp(index, "level") == 0) {
        if (lua_isuserdata(L, -1)) {
            Level* level = (Level*)lua_touserdata(L, -1);
            game->level = level;
            //printf("Game: set 'level' with name '%s' to game object\n", game->level->name.c_str());
        }
        else {
            printf("Game: trying set 'level' to wrong data type! Got %s, userdata (LevelMetaTable) required.\n", lua_typename(L, lua_type(L, -1)));
            if (lua_isnil(L, -1)) {
                game->level = nullptr;
            }
        }
    } else {
        printf("Game: user trying to add unknown field '%s' to the object\n", index);
    }
    return 0;
}


int LuaObjectParser::_tostringGame(lua_State* L) {
    using namespace LuaGen;
    Game* game = (Game*)lua_touserdata(L, -1);
    std::stringstream ss;
    ss << "Game object memaddr=" << (void const*)game << ", name=" << game->name << ", level=" << ( game->level == nullptr ? 0 : game->level->width);
    std::string s = ss.str();
    lua_pushstring(L, s.c_str());
    return 1;
}

int LuaObjectParser::_concatstringGame(lua_State* L) {
    using namespace LuaGen;

    std::string leftString = "";
    std::string rightString = "";

    bool leftIsString = false;

    if (lua_isstring(L, -2) && lua_isuserdata(L, -1) ) {
        leftIsString = true;
        leftString = std::string(lua_tostring(L, -2));
        Game* game = (Game*)lua_touserdata(L, -1);
        std::stringstream ss;
        ss << "Game object memaddr=" << (void const*)game << ", name=" << game->name;
        rightString = ss.str();
    }

    if (lua_isstring(L, -1) && lua_isuserdata(L, -2)) {
        leftString = std::string(lua_tostring(L, -1));
        Game* game = (Game*)lua_touserdata(L, -2);
        std::stringstream ss;
        ss << "Game object memaddr=" << (void const*)game << ", name=" << game->name;
        rightString = ss.str();
    }

    if (leftIsString) {
        lua_pushstring(L, (leftString + rightString).c_str());
    }
    else {
        lua_pushstring(L, (rightString + leftString).c_str());
    }
    
    return 1;
}

LuaGen::Game* LuaObjectParser::GetGame(lua_State* L, const char* objectName) {
    lua_getglobal(L, objectName);
    if (lua_isuserdata(L, -1)) {
        LuaGen::Game* game = (LuaGen::Game*)lua_touserdata(L, -1);
        //printf("Returning game : %s, level name=%s\n", game->name.c_str(), game->level->name.c_str());
        return game;
    }
    printf("Object %s (Game) not found !!!\n", objectName);
    return nullptr;
}

// =========================================

