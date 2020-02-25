#pragma once
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <functional>
#include <Resources.h>

extern "C"
{
	#include<lua.h>
	#include<lauxlib.h>
	#include<lualib.h>
}

class LuaVM
{
public:
	LuaVM();

	bool DoString(std::string code);
	bool DoFile(std::string file_location);
	std::pair<int, std::string> check_error_msg();

	lua_State* get_L();

	float getVarNum(std::string var, int stack_depth = -1);
	std::string getVarStr(std::string var, int stack_depth = -1);

	int newtable(std::string name);
	void newmetatable(std::string name);
	void setmetatable(std::string name, int stk_id = -1);
	void pushfunction(std::string name, int(*fun)(lua_State * L));
	void setfunction(std::string name,  int(*fun)(lua_State * L));
	void setvalue(std::string name, int val_id);
	void AddToGlobal(std::string name, void* var);
	void setlightuserdata(std::string name, void* var);

	~LuaVM();

private:
	lua_State* L;
	int errcode;
	std::string errstr;
};

extern LuaVM LUA;