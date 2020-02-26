#include "LuaVM.h"

LuaVM LUA;

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

std::pair<int, std::string> LuaVM::check_error_msg()
{
	return std::pair<int, std::string>(errcode, errstr);
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

int LuaVM::newtable(std::string name)
{
	lua_newtable(L);
	//get id of the top element of the stack
	int TableIdx = lua_gettop(L);
	//push table id to stack
	lua_pushvalue(L, TableIdx);
	//create a global object with this id
	lua_setglobal(L, name.c_str());
	return TableIdx;
}

//void LuaVM::runfunction(int stk_id, int in, int out = 1)

void LuaVM::newmetatable(std::string name)
{
	luaL_newmetatable(L, name.c_str());
}

void LuaVM::setmetatable(std::string name, int stk_id)
{
	luaL_getmetatable(L, name.c_str());
	lua_setmetatable(L, stk_id-1);
}

void * LuaVM::newuserdata(int size)
{
	return lua_newuserdata(L, size);
}

void LuaVM::newuserdatafrom(void* data, std::string metatable)
{
	//assuming that Lua only stores the pointer as userdata
	void** obj = (void**)lua_newuserdata(L, sizeof(void*));
	*obj = data; //set the pointer to point at the data
	luaL_getmetatable(L, metatable.c_str());
	lua_setmetatable(L, -2);
}

void LuaVM::newuserdatafrom(std::string name, void* data, std::string metatable)
{
	newuserdatafrom(data, metatable);
	lua_setglobal(L, name.c_str());
}

void LuaVM::pushfunction(std::string name, int(*fun)(lua_State * L))
{
	//push function pointer to stack
	lua_pushcfunction(L, fun);
	lua_setglobal(L, name.c_str());
}

void LuaVM::setfunction(std::string name, int(*fun)(lua_State * L))
{
	lua_pushstring(L, name.c_str());
	lua_pushcfunction(L, fun);
	lua_settable(L, -3);
}

void LuaVM::setvalue(std::string name, int val_id)
{
	lua_pushstring(L, name.c_str());
	//push index to top
	lua_pushvalue(L, val_id);
	lua_settable(L, -3);
}

void LuaVM::AddToGlobal(std::string name, void* var)
{
	lua_pushlightuserdata(L, var);
	lua_setglobal(L, name.c_str());
}

void LuaVM::setlightuserdata(std::string name, void* var)
{
	lua_pushstring(L, name.c_str());
	lua_pushlightuserdata(L, var);
	lua_settable(L, -3);
}

LuaVM::~LuaVM()
{
	lua_close(L);
}

lua_State* LuaVM::get_L()
{
	return L;
}
