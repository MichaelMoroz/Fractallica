#include "InterfaceLua.h"

void WrapInterface(LuaVM* LVM)
{
	auto CreateObject = [](lua_State* L) -> int
	{
		void* pointerToASprite = lua_newuserdata(L, sizeof(Object));
		new (pointerToASprite) Object();
		luaL_getmetatable(L, "ObjectMetaTable");
		lua_setmetatable(L, -2);
		return 1;
	};

	auto DestroyObject = [](lua_State* L) -> int
	{
		Object* sprite = (Object*)lua_touserdata(L, -1);
		sprite->~Object();
		return 0;
	};

	lua_State* L = LUA.get_L();

	lua_newtable(L);
	int spriteTableIdx = lua_gettop(L);
	lua_pushvalue(L, spriteTableIdx);
	lua_setglobal(L, "Sprite");

	lua_pushcfunction(L, CreateObject);
	lua_setfield(L, -2, "new");

	luaL_newmetatable(L, "SpriteMetaTable");
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, DestroyObject);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushvalue(L, spriteTableIdx);
	lua_settable(L, -3);
}
