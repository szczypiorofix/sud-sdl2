#pragma once

extern "C" {
	#include <lua542/lua.hpp>
}

#include <iostream>
#include "PlayerParser.h"
#include "GameParser.h"

namespace LUA {
    namespace Parser {

        class Parser {
        public:

            static void TestStack(lua_State* L) {
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
        };
    }
}
