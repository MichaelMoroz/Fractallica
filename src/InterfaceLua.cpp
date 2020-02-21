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

	auto OpenWindow = [](lua_State* L) -> int
	{
		float posX = lua_tonumber(L, -2);
		float posY = lua_tonumber(L, -1);
		void* pointerToASprite = lua_newuserdata(L, sizeof(Window));
		new (pointerToASprite) Window(posX, posY, 200.f, 200.f, sf::Color(100, 0, 0, 128), LOCAL["TEST"], LOCAL("default"));
		luaL_getmetatable(L, "WindowMetaTable");
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

	//push table to stack
	lua_newtable(L);
	//get id of the top element of the stack
	int spriteTableIdx = lua_gettop(L);
	//push table id to stack
	lua_pushvalue(L, spriteTableIdx);
	//create a global object with this id
	lua_setglobal(L, "Object");

	//push function poiter to stack
	lua_pushcfunction(L, CreateObject);
	//does the equivalent to table[key] = value at top of stack
	lua_setfield(L, -2, "new");

	//push new metatable to metatable stack
	luaL_newmetatable(L, "ObjectMetaTable");
	//push string to top
	lua_pushstring(L, "__gc");
	//push function to top
	lua_pushcfunction(L, DestroyObject);
	//does the equivalent to table[key] = value at top of stack -1, and key is on top
	lua_settable(L, -3);

	//push string to top
	lua_pushstring(L, "__index");
	//push index to top
	lua_pushvalue(L, spriteTableIdx);
	//does the equivalent to table[key] = valuee at top of stack -1, and key is on top
	lua_settable(L, -3);
}
