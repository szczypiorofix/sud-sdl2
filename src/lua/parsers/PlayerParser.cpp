#include <sstream>
#include <assert.h>
#include "PlayerParser.h"
#include "../LuaHelper.h"



void PlayerParser::RegisterObject(lua_State* L) {

    // New table
    lua_newtable(L);
    // Player table index on Lua stack 
    int gameTableIdx = lua_gettop(L);
    lua_pushvalue(L, gameTableIdx);
    lua_setglobal(L, "Player");

    // Player contructor
    lua_pushcfunction(L, PlayerParser::_new);
    lua_setfield(L, -2, "new");

    // Player Move method
    lua_pushcfunction(L, PlayerParser::Move);
    lua_setfield(L, -2, "Move");

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

   
    // SET GLOBAL FUNCTION FOR PLAYER
    //lua_pushcfunction(L, PlayerParser::MovePlayer);
    //lua_setglobal(L, "MovePlayer");

}


int PlayerParser::_new(lua_State* L) {
    //printf("Player: constructor\n");

    void* pointerToPlayer = lua_newuserdata(L, sizeof(LuaPlayer));
    LuaPlayer* player = new (pointerToPlayer) LuaPlayer();

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
        
        lua_settop(L, 3);
    }
    else {
        lua_setmetatable(L, 2); // assign metatable (PlayerMetaTable) to userdata
        
        //lua_newtable(L);
        //lua_setuservalue(L, 1);

        // userdata is on top of the stack
    }

    lua_newtable(L);
    lua_setuservalue(L, 3);

    //Parser::TestStack(L);

    return 1;
}

int PlayerParser::_destroy(lua_State* L) {
    LuaPlayer* player = (LuaPlayer*)lua_touserdata(L, -1);
    player->~LuaPlayer();
    //printf("Player: destroy\n");
    return 0;
}

int PlayerParser::_tostring(lua_State* L) {
    LuaPlayer* player = (LuaPlayer*)lua_touserdata(L, -1);
    std::stringstream ss;
    ss << "Player.__tostring memaddr=" << (void const*)player << ", name=" << player->name << ", x=" << player->y << ", y=" << player->x;
    std::string s = ss.str();
    lua_pushstring(L, s.c_str());
    return 1;
}


int PlayerParser::_index(lua_State* L) {
    assert( lua_isuserdata(L, 1) ); // 1
    assert( lua_isstring(L, 2) );   // 2

    LuaPlayer* player = (LuaPlayer*)lua_touserdata(L, 1);
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
    else if (strcmp(index, "Move") == 0) {
        printf("Assigning LUA Move function?\n");
        lua_pushcfunction( L, PlayerParser::MovePlayer );
        lua_getuservalue(L, 1);
        lua_pushvalue(L, 2);
        lua_gettable(L, -2);
        lua_pushcfunction(L, PlayerParser::MovePlayer);
        LuaHelper::TestStack(L);
        lua_setfield(L, 2, "Move");
        LuaHelper::TestStack(L);
    }
    else {
        
        lua_getuservalue(L, 1);
        lua_pushvalue(L, 2);
        lua_gettable(L, -2);

        if (lua_isnil(L, -1)) {
            lua_getglobal(L, "Player");
            lua_pushstring(L, index);
            lua_rawget(L, -2);
        }

    }
    return 1;
}

int PlayerParser::_newindex(lua_State* L) {
    assert(lua_isuserdata(L, 1)); // 1
    assert(lua_isstring(L, 2));   // 2
    // key -                      // 3

    LuaPlayer* player = (LuaPlayer*)lua_touserdata(L, 1);
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
    else if (strcmp(index, "width") == 0) {
        if (lua_isnumber(L, -1)) {
            lua_Number width = lua_tonumber(L, -1);
            player->width = (int)width;
        }
        else {
            printf("Player: trying set 'width' to wrong data type! Got %s, int required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else if (strcmp(index, "height") == 0) {
        if (lua_isnumber(L, -1)) {
            lua_Number height = lua_tonumber(L, -1);
            player->height = (int)height;
        }
        else {
            printf("Player: trying set 'height' to wrong data type! Got %s, int required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else if (strcmp(index, "Move") == 0) {
        if (lua_isfunction(L, -1)) {
            printf("Set new value to player:Move() method\n");
            //int (Player:: * DrawPointer)(void) = NULL;
            //DrawPointer = &Player::Draw;
            //int result = (*player.*DrawPointer)();
            //printf("Calling object method pointer? No problema! Result=%i\n", result);
            
            //lua_remove(L, 1);
            //lua_remove(L, 1);
            /*LuaHelper::TestStack(L);*/
            //if (lua_pcall(L, 0, 1, 0) != 0) {
            //    printf("LUA: Call error: %s\n", lua_tostring(L, -1));
            //}
            /*lua_pushcfunction(L, PlayerParser::MovePlayer);*/


            LuaHelper::TestStack(L);

        }
        else {
            printf("Player: trying set 'Move' to wrong data type! Got %s, int required.\n", lua_typename(L, lua_type(L, -1)));
        }
    }
    else {
        printf("Player: assign unknown data of type %s to player as '%s' field\n", lua_typename(L, lua_type(L, -1)), index);
        lua_getuservalue(L, 1); // 1 - player table
        lua_pushvalue(L, 2);    // 2 - index
        lua_pushvalue(L, 3);    // 3 - value
        lua_settable(L, -3);    // 1[2] = 3
    }
    return 0;
}

LuaPlayer* PlayerParser::GetPlayer(lua_State* L, const char* playerName) {
    lua_getglobal(L, playerName);
    if (lua_isuserdata(L, -1)) {
        LuaPlayer* player = (LuaPlayer*)lua_touserdata(L, -1);
        return player;
    }
    printf("Object %s (Player) not found !!!\n", playerName);
    return nullptr;
}


int PlayerParser::Move(lua_State* L) {
    LuaPlayer* player = (LuaPlayer*)lua_touserdata(L, lua_upvalueindex(1));
    //return player->Move(L);

    printf("Player:Move() assign method to Player object\n");

    if (lua_isfunction(L, -1)) {
        printf("OK, its a function!\n");
        //
        //
        //
    }

    //lua_pushstring(L, "moj obiekt");

    LuaHelper::TestStack(L);

    return 0;
}


int PlayerParser::MovePlayer(lua_State* L) {
    printf("PlayerParser::MovePlayer call\n");

    /*Player* player = (Player*)lua_touserdata(L, lua_upvalueindex(1));
    return player->Move(L);*/

    if (lua_isuserdata(L, -1)) {
        // ok first parameter is userdata
        //printf("PlayerParser::MovePlayer first parameter is userdata\n");
    }

    //LuaHelper::TestStack(L);

    return 1;
}

