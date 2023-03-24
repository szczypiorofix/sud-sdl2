#include "TestParser.h"
#include "../LuaHelper.h"




void TestParser::RegisterObject(lua_State* L) {

	//lua_getglobal(L, "testFunction");

	
	//lua_newtable(L);
	//lua_pushstring(L, "testFunction");
	//lua_pushcfunction(L, TestParser::TestFunction);
	//lua_settable(L, -3);

	//lua_pushstring(L, "duuppa");
	//lua_pushcfunction(L, TestParser::TestFunction);
	//lua_setglobal(L, "TestFunction");

}

void TestParser::ResolveObjects(lua_State* L) {
	
	//lua_getglobal(L, "funcs");
	//lua_getfield(L, -1, "on_mouse_click");
	//if (!lua_isnil(L, -1)) {
	//	lua_call(L, 0, 0);
	//}
	//else {
	//	// nothing registered
	//}

	//player_draw_registry_value = 1;

	//if (player_draw_registry_value != 0) {
	//	lua_rawgeti(L, LUA_REGISTRYINDEX, player_draw_registry_value);
	//	//LuaHelper::TestStack(L);
	//	lua_call(L, 0, 0);
	//}
	//else {
	//	// No mouse handler was registered.
	//	printf("No player draw was registerd\n");
	//}


}


int TestParser::register_player_draw(lua_State* L) {
	player_draw_registry_value = luaL_ref(L, LUA_REGISTRYINDEX);
	return 0;
}

int TestParser::TestFunction(lua_State* L) {
	
	LuaHelper::TestStack(L);

	//if (lua_istable(L, -1)) {
	//	lua_getfield(L, -1, "name");
	//	name = lua_tostring(L, -1);
	//}

	//if (lua_isfunction(L, -1)) {
	//	printf("Searching for function\n");
	//	TestObject testObject;
	//	testObject.Call(L);
	//}


	return 0;
}
