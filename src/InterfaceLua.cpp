#include "InterfaceLua.h"

const char* ObjectLua::className = "Object";
const Luna < ObjectLua >::FunctionType ObjectLua::Functions[] = {
		{"Create", &ObjectLua::Create},
		{0}
};

int ObjectLua::Create(lua_State* L)
{
	
}

void WrapInterface(LuaVM* LVM)
{
	Luna < ObjectLua >::Register(LVM., "Interface");
}
