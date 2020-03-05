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
#include <Shaders.h>
#include <Renderer.h>
#include <Interface.h>
#include <Gamemodes.h>


/*
	Lua Fractallica shader classes wrapper
*/

void WrapShaders(LuaVM* LVM);
