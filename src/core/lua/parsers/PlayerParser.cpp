#include "PlayerParser.h"
#include <sstream>
#include <assert.h>


void LUA::Parser::PlayerParser::RegisterObject(lua_State* L) {

    // New table
    lua_newtable(L);
    // Player table index on Lua stack 
    int gameTableIdx = lua_gettop(L);
    lua_pushvalue(L, gameTableIdx);
    lua_setglobal(L, "Player");

    // Player contructor
    lua_pushcfunction(L, PlayerParser::_new);
    lua_setfield(L, -2, "new");

    // ============== metamethods =====================
    // Creating new metatable
    luaL_newmetatable(L, "PlayerMetaTable");

    lua_pushstring(L, "__gc"); // Garbage Collector metamethod - runs Player destructor
    lua_pushcfunction(L, PlayerParser::_destroy);
    lua_settable(L, -3);

    lua_pushstring(L, "__tostring"); // tostring metamethod override
    lua_pushcfunction(L, PlayerParser::_tostring);
    lua_settable(L, -3);

    lua_pushstring(L, "__index"); // seting the proper index for PlayerMetaTable
    lua_pushcfunction(L, PlayerParser::_index);
    lua_settable(L, -3);

    lua_pushstring(L, "__newindex"); // seting the proper new index for PlayerMetaTable
    lua_pushcfunction(L, PlayerParser::_newindex);
    lua_settable(L, -3);
}


int LUA::Parser::PlayerParser::_new(lua_State* L) {
    using namespace LUA::Object;

    //printf("Player: constructor\n");

    void* pointerToPlayer = lua_newuserdata(L, sizeof(Player));
    Player* player = new (pointerToPlayer) Player();

    // checking table as a parameter??
    int tableId = 0;

    if (lua_istable(L, 2)) {
        tableId = 2; // constructor parameter is table!
    }

    luaL_getmetatable(L, "PlayerMetaTable");
    assert(lua_istable(L, -1)); // check if last lua stack item - metatable - is a table

    if (tableId > 0 && lua_istable(L, tableId)) {
        lua_setmetatable(L, 3); // assign metatable (PlayerMetaTable) to userdata

        lua_getfield(L, tableId, "x");
        if (lua_isnumber(L, -1)) {
            lua_Number x = lua_tonumber(L, -1);
            player->x = (int)x;
        }
        
        lua_getfield(L, tableId, "y");
        if (lua_isnumber(L, -1)) {
            lua_Number y = lua_tonumber(L, -1);
            player->y = (int)y;
        }

        lua_getfield(L, tableId, "name");
        if (lua_isstring(L, -1)) {
            const char* name = lua_tostring(L, -1);
            player->name = name;
        }

        lua_getfield(L, tableId, "width");
        if (lua_isstring(L, -1)) {
            lua_Number width = lua_tonumber(L, -1);
            player->width = (int)width;
        }

        lua_getfield(L, tableId, "height");
        if (lua_isstring(L, -1)) {
            lua_Number height = lua_tonumber(L, -1);
            player->height = (int)height;
        }

        lua_getfield(L, tableId, "OnDraw");
        if (lua_isfunction(L, -1)) {
            printf("OnDraw is function!\n");
            
            
            //LUA::Parser::Parser::TestStack(L);

        }
        
        //LUA::Parser::Parser::TestStack(L);

        lua_settop(L, 3);

    }
    else {
        lua_setmetatable(L, 2); // assign metatable (PlayerMetaTable) to userdata
        
        //lua_newtable(L);
        //lua_setuservalue(L, 1);

        // userdata is on top of the stack
    }

    //LUA::Parser::Parser::TestStack(L);

    return 1;
}

int LUA::Parser::PlayerParser::_destroy(lua_State* L) {
    using namespace LUA::Object;
    Player* player = (Player*)lua_touserdata(L, -1);
    player->~Player();
    //printf("Player: destroy\n");
    return 0;
}

int LUA::Parser::PlayerParser::_tostring(lua_State* L) {
    using namespace LUA::Object;
    Player* player = (Player*)lua_touserdata(L, -1);
    std::stringstream ss;
    ss << "Player.__tostring memaddr=" << (void const*)player << ", name=" << player->name << ", x=" << player->y << ", y=" << player->x;
    std::string s = ss.str();
    lua_pushstring(L, s.c_str());
    return 1;
}

int LUA::Parser::PlayerParser::_index(lua_State* L) {
    using namespace LUA::Object;

    assert( lua_isuserdata(L, 1) );
    assert( lua_isstring(L, 2) );

    Player* player = (Player*)lua_touserdata(L, 1);
    const char* index = lua_tostring(L, 2);

    if (strcmp(index, "x") == 0) {
        lua_pushnumber(L, player->x);
    }
    else if (strcmp(index, "y") == 0 ) {
        lua_pushnumber(L, player->y);
    }
    else if (strcmp(index, "width") == 0) {
        lua_pushnumber(L, player->width);
    }
    else if (strcmp(index, "height") == 0) {
        lua_pushnumber(L, player->height);
    }
    else if (strcmp(index, "name") == 0) {
        lua_pushstring(L, player->name.c_str());
    }
    else if (strcmp(index, "OnDraw") == 0) {
        lua_pushcclosure(L, PlayerParser::_OnDraw, 1 );
    }
    else {
        lua_getglobal(L, "Player");
        lua_pushstring(L, index);
        lua_rawget(L, -2);
    }
    return 1;
}

int LUA::Parser::PlayerParser::_newindex(lua_State* L) {
    using namespace LUA::Object;

    assert(lua_isuserdata(L, 1));
    assert(lua_isstring(L, 2));

    Player* player = (Player*)lua_touserdata(L, 1);
    const char* index = lua_tostring(L, 2);
    
    if ( strcmp(index, "x" ) == 0 ) {
        if (lua_isnumber(L, -1)) {
            lua_Number x = lua_tonumber(L, -1);
            player->x = (int)x;
        }
        else {
            printf("Player: trying set 'x' to wrong data type! Got %s, int required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else if (strcmp(index, "y") == 0) {
        if (lua_isnumber(L, -1)) {
            lua_Number y = lua_tonumber(L, -1);
            player->y = (int)y;
        }
        else {
            printf("Player: trying set 'y' to wrong data type! Got %s, int required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else if (strcmp(index, "OnDraw") == 0) {
        if (lua_isfunction(L, -1)) {
            printf("Player: calling OnDraw function!\n");
            
            void* playerPointer = lua_newuserdata(L, sizeof(Player));
            Player* pl = new(playerPointer) Player(*player);
            luaL_getmetatable(L, "PlayerMetaTable");
            assert(lua_istable(L, -1));
            lua_setmetatable(L, -2);

            if (lua_isuserdata(L, -1)) {
                //LUA::Parser::Parser::TestStack(L);
                lua_pcall(L, 1, 0, 0);
            }
            else {
                printf("Player: trying to set OnDraw method but got wrong data on top of the stack! Got %s, userdata required.\n", lua_typename(L, lua_type(L, -1)));
            }
        }
        else {
            printf("Player: trying set 'OnDraw' to wrong data type! Got %s, function required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else {
        printf("Player: user trying to add an object of type '%s' to an unknown field '%s'\n", lua_typename(L, lua_type(L, -1)), index);
    }
    return 0;
}

LUA::Object::Player* LUA::Parser::PlayerParser::GetPlayer(lua_State* L, const char* playerName) {
    using namespace LUA::Object;
    lua_getglobal(L, playerName);
    if (lua_isuserdata(L, -1)) {
        Player* player = (Player*)lua_touserdata(L, -1);
        return player;
    }
    printf("Object %s (Player) not found !!!\n", playerName);
    return nullptr;
}

int LUA::Parser::PlayerParser::_OnDraw(lua_State* L) {
    using namespace LUA::Object;
    Player* player = static_cast<Player*>(lua_touserdata(L, lua_upvalueindex(1)));
    return player->OnDraw(L);
}

