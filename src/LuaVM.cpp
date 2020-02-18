#include "LuaVM.h"

LuaVM::LuaVM()
{
	errcode = LUA_OK;
	L = luaL_newstate();
	//standard Lua libraries
	luaL_openlibs(L);
}

bool LuaVM::DoString(std::string code)
{
	errcode = luaL_dostring(L, code.c_str());
	if (errcode == LUA_OK)
	{
		return true; 
	}
	else
	{
		errstr = lua_tostring(L, -1);
		return false;
	}
}

bool LuaVM::DoFile(std::string file_location)
{
	errcode = luaL_dofile(L, file_location.c_str());
	if (errcode == LUA_OK)
	{
		return true;
	}
	else
	{
		errstr = lua_tostring(L, -1);
		return false;
	}
}

std::string LuaVM::check_error_msg()
{
	return errstr;
}

float LuaVM::getVarNum(std::string var, int stack_depth)
{
	lua_getglobal(L, var.c_str());
	if (lua_isnumber(L, stack_depth))
	{
		return (float)lua_tonumber(L, stack_depth);
	}
	else return 0.0f; //NaN
}

std::string LuaVM::getVarStr(std::string var, int stack_depth)
{
	if (lua_isstring(L, stack_depth))
	{
		return std::string(lua_tostring(L, stack_depth));
	}
	else return std::string();
}

LuaVM::~LuaVM()
{
	lua_close(L);
}
