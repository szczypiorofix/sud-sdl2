#pragma once

#include <lua535/lua.hpp>
#include <iostream>
#include <vector>


#define LUA_MYOBJECT "TestModel"


class TestModel {
public:
	TestModel( int _x ) : x( _x ) { }
	void set( int _x ) {
		this->x = _x;
	}
	int get() const {
		return this->x;
	}

private:
	int x;

};



class LuaHandler {

public:
	LuaHandler();

	~LuaHandler( void );

	bool LoadFile(const std::string fileName);

	bool ProcessText(const char* content);


	bool GetGlobal( const char* name );

	bool GetInt( const char* variableName, int& value );

	bool GetFunctionStringTuple( const char* functionName, std::vector<std::string>& returnValues, const int returnValuesCounter );

	bool GetFunctionIntValue( const char* functionName, int& value );

	void Close(void);

	void RegisterObject();


private:
	lua_State* luaState;

	void Open(void);

	static int myobject_new( lua_State* L );
	static int myobject_delete( lua_State* L );
	static int myobject_set( lua_State* L );
	static int myobject_get( lua_State* L );

};
