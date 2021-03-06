#pragma once
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <Resources.h>

#include <new>
#include <LuaVM.h>
#include <Interface.h>
#include <Gamemodes.h>
/*
	Lua Fractallica interface classes wrapper
*/

void WrapInterface(LuaVM* LVM);

void AddObject2LuaStack(LuaVM* LVM, Object* obj);
call_func GetLuaCallbackFunction(lua_State* L);

