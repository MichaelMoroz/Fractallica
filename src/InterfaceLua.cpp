#include "InterfaceLua.h"

void WrapInterface(LuaVM* LVM)
{
	/* 
		Object base class wrapper
	*/

	///Object table
	//push table to stack
	int objid = LUA.newtable("Object");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			void* newobj = lua_newuserdata(L, sizeof(Object));
			new (newobj) Object();
			luaL_getmetatable(L, "ObjectMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("SetPosition", [](lua_State* L) -> int
		{
			Object* obj = (Object*)lua_touserdata(L, -3);
			float posX = lua_tonumber(L, -2);
			float posY = lua_tonumber(L, -1);
			obj->SetPosition(posX, posY);
			return 1;
		});

	LUA.newmetatable("ObjectMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Object* obj = (Object*)lua_touserdata(L, -1);
			obj->~Object();
			return 0;
		});
	
	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", objid);

	/*
		Box child class wrapper
	*/
	int boxid = LUA.newtable("Box");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			float dX = lua_tonumber(L, -2);
			float dY = lua_tonumber(L, -1);
			void* newobj = lua_newuserdata(L, sizeof(Box));
			new (newobj) Box(dX, dY);
			luaL_getmetatable(L, "BoxMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	//inheritance of Object methods
	LUA.setmetatable("ObjectMetaTable");

	LUA.newmetatable("BoxMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Box* obj = (Box*)lua_touserdata(L, -1);
			obj->~Box();
			return 0;
		});
	LUA.setvalue("__index", boxid);
	
	///Add global object
	LUA.pushfunction("AddGlobalObject", [](lua_State* L) -> int
		{
			Object* obj = (Object*)lua_touserdata(L, -1);
			AddGlobalObject(*obj);
			return 1;
		});

	///test stuff
	LUA.pushfunction("OpenTestWindow", [](lua_State* L) -> int
		{
			OpenTestWindow();
			return 1;
		});
}
