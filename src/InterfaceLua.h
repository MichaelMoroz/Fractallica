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
/*
	Lua Fractallica interface classes wrapper
*/


/*
	Object Base class wrapper
*/
class ObjectLua
{


public:
	ObjectLua(): isPrecious(false)
	{}

	static int Create(lua_State* L);

	// declaration
	static const char* className;
	static const Luna < ObjectLua >::FunctionType Functions[];
	static const Luna < ObjectLua >::PropertyType Properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your classes constructor.
};

void WrapInterface(LuaVM* LVM);
