#pragma once
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
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
	std::string check_error_msg();

	float getVarNum(std::string var, int stack_depth = -1);
	std::string getVarStr(std::string var, int stack_depth = -1);

	~LuaVM();

private:
	lua_State* L;
	int errcode;
	std::string errstr;
};