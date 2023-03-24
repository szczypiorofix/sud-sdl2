#include "GameParser.h"
#include <sstream>
#include <assert.h>




void GameParser::RegisterObject(lua_State* L) {

    //GameParser::RegisterLevelObject(L);

    // New table
    lua_newtable(L);
    // Game table index on Lua stack 
    int gameTableIdx = lua_gettop(L);
    lua_pushvalue(L, gameTableIdx);
    lua_setglobal(L, "Game");

    // Game contructor
    lua_pushcfunction(L, GameParser::_new);
    lua_setfield(L, -2, "new");

    // Init method
    lua_pushcfunction(L, GameParser::Init);
    lua_setfield(L, -2, "init");


    // ============== metamethods =====================
    // Creating new metatable
    luaL_newmetatable(L, "GameMetaTable");

    lua_pushstring(L, "__gc"); // Garbage Collector metamethod - runs Game destructor
    lua_pushcfunction(L, GameParser::_destroy);
    lua_settable(L, -3);

    lua_pushstring(L, "__tostring"); // tostring metamethod override
    lua_pushcfunction(L, GameParser::_tostring);
    lua_settable(L, -3);

    lua_pushstring(L, "__concat"); // concatenation of string metamethod override
    lua_pushcfunction(L, GameParser::_concatstring);
    lua_settable(L, -3);

    lua_pushstring(L, "__index"); // seting the proper index for GameMetaTable
    lua_pushcfunction(L, GameParser::_index);
    lua_settable(L, -3);

    lua_pushstring(L, "__newindex"); // seting the proper new index for GameMetaTable
    lua_pushcfunction(L, GameParser::_newindex);
    lua_settable(L, -3);
}


int GameParser::_new(lua_State* L) {
    //printf("Game: new\n");

    void* pointerToAGame = lua_newuserdata(L, sizeof(LuaGame));
    LuaGame* game = new (pointerToAGame) LuaGame("default_game");
    game->level = new LuaLevel();

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


int GameParser::_destroy(lua_State* L) {
    LuaGame* game = (LuaGame*)lua_touserdata(L, -1);
    game->~LuaGame();
    //printf("Game: destroy\n");
    return 0;
};

// Getter
int GameParser::_index(lua_State* L) {
    assert(lua_isuserdata(L, 1)); // userdata - 1 (game)
    assert(lua_isstring(L, 2));   // string   - 2 (parameter)

    LuaGame* game = (LuaGame*)lua_touserdata(L, 1);
    const char* index = lua_tostring(L, 2);

    if (strcmp(index, "name") == 0) {
        lua_pushstring(L, game->name.c_str());
        return 1;
    } else if (strcmp(index, "windowWidth") == 0) {
        lua_pushnumber(L, game->windowWidth);
        return 1;
    } else if (strcmp(index, "windowHeight") == 0) {
        lua_pushnumber(L, game->windowHeight);
        return 1;
    } else if (strcmp(index, "level") == 0) {
        void* levelPointer = lua_newuserdata(L, sizeof(LuaLevel));
        LuaLevel* tl = new(levelPointer) LuaLevel(*game->level);
        //printf("TempLevel %s\n", tl->name.c_str());

        luaL_getmetatable(L, "LevelMetaTable");
        assert(lua_istable(L, -1));
        lua_setmetatable(L, -2);

        //TestStack(L);

        return 1;
    }
        /*else if (strcmp(index, "init") == 0) {
        printf("Calling game:init()\n");
        
        int (Game:: * pt2Member)(lua_State *LL) = NULL;
        pt2Member = &Game::Init;

        int result4 = (game->*pt2Member)(L);

        lua_pushstring(L, "init");
        lua_rawget(L, -2);

        printf("Pointer from game->init = %i\n", result4);
        
        
        Parser::TestStack(L);

        return 1;
    }*/
        else {
        lua_getglobal(L, "Game");
        lua_pushstring(L, index);
        lua_rawget(L, -2);
        return 1;
    }
}

//Setter
int GameParser::_newindex(lua_State* L) {
    assert(lua_isuserdata(L, 1));
    assert(lua_isstring(L, 2));

    LuaGame* game = (LuaGame*)lua_touserdata(L, 1);
    const char* index = lua_tostring(L, 2);

    if (strcmp(index, "name") == 0) {
        if (lua_isstring(L, -1)) {
            const char* name = lua_tostring(L, -1);
            game->name = name;
        }
        else {
            printf("Game: trying set 'name' to wrong data type! Got %s, string required.\n", lua_typename(L, lua_type(L, -1)));
        }
    } else if (strcmp(index, "windowWidth") == 0) {
        if (lua_isnumber(L, -1)) {
            lua_Number windowWidth = lua_tonumber(L, -1);
            game->windowWidth = (int)windowWidth;
        }
        else {
            printf("Game: trying set 'windowWidth' to wrong data type! Got %s, number required.\n", lua_typename(L, lua_type(L, -1)));
        }
    } else if (strcmp(index, "windowHeight") == 0) {
        if (lua_isnumber(L, -1)) {
            lua_Number windowHeight = lua_tonumber(L, -1);
            game->windowHeight = (int)windowHeight;
        }
        else {
            printf("Game: trying set 'windowHeight' to wrong data type! Got %s, number required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else if (strcmp(index, "level") == 0) {
        if (lua_isuserdata(L, -1)) {
            LuaLevel* level = (LuaLevel*)lua_touserdata(L, -1);
            game->level = level;
        }
        else {
            printf("Game: trying set 'level' to wrong data type! Got %s, userdata (LevelMetaTable) required.\n", lua_typename(L, lua_type(L, -1)));
            if (lua_isnil(L, -1)) {
                game->level = nullptr;
            }
        }
    }
    else {
        printf("Game: user trying to add an object of type '%s' to an unknown field '%s'\n", lua_typename(L, lua_type(L, -1)), index);
    }
    return 0;
}


int GameParser::_tostring(lua_State* L) {
    LuaGame* game = (LuaGame*)lua_touserdata(L, -1);
    std::stringstream ss;
    ss << "Game object memaddr=" << (void const*)game << ", name=" << game->name << ", level=" << (game->level == nullptr ? 0 : game->level->width);
    std::string s = ss.str();
    lua_pushstring(L, s.c_str());
    return 1;
}

int GameParser::_concatstring(lua_State* L) {
    std::string leftString = "";
    std::string rightString = "";

    bool leftIsString = false;

    if (lua_isstring(L, -2) && lua_isuserdata(L, -1)) {
        leftIsString = true;
        leftString = std::string(lua_tostring(L, -2));
        LuaGame* game = (LuaGame*)lua_touserdata(L, -1);
        std::stringstream ss;
        ss << "Game object memaddr=" << (void const*)game << ", name=" << game->name;
        rightString = ss.str();
    }

    if (lua_isstring(L, -1) && lua_isuserdata(L, -2)) {
        leftString = std::string(lua_tostring(L, -1));
        LuaGame* game = (LuaGame*)lua_touserdata(L, -2);
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

LuaGame* GameParser::GetGame(lua_State* L, const char* gameName) {
    lua_getglobal(L, gameName);
    if (lua_isuserdata(L, -1)) {
        LuaGame* game = (LuaGame*)lua_touserdata(L, -1);
        //printf("Returning game : %s, level name=%s\n", game->name.c_str(), game->level->name.c_str());
        return game;
    }
    printf("Object %s (Game) not found !!!\n", gameName);
    return nullptr;
}

int GameParser::Init(lua_State* L) {
    int windowWidth = LuaGame::DEFAULT_WINDOW_WIDTH;
    int windowHeight = LuaGame::DEFAULT_WINDOW_HEIGHT;

    // Checking if seond element on stack is table (first parameter)
    if (lua_istable(L, -1)) {       
        lua_getfield(L, -1, "windowWidth");
        lua_Integer wW = lua_tointeger(L, -1);
        windowWidth = (int)wW;
        
        lua_getfield(L, -2, "windowHeight");
        lua_Integer wH = lua_tointeger(L, -1);
        windowHeight = (int)wH;
    }

    // Second parameter is userdata
    LuaGame* game = (LuaGame*)lua_touserdata(L, 1);
    if (game != nullptr) {
        return game->Init( windowWidth, windowHeight );
    }
    return 0;
}


