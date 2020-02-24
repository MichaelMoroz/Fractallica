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
#include <Shaders.h>

/*
	Lua Fractallica shader classes wrapper
*/

void WrapShaders(LuaVM* LVM);
