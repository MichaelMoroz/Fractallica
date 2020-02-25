#pragma once
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

#include <new>
#include <LuaVM.h>
#include <Shaders.h>
#include <Interface.h>
#include <Gamemodes.h>

void WrapResources(LuaVM* LVM);
void AddToGlobalLua(std::string name, sf::Texture* txt);