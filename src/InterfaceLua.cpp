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
	LUA.setfunction("AddObject", [](lua_State* L) -> int
		{
			Object* obj = (Object*)lua_touserdata(L, -3);
			Object* obj0 = (Object*)lua_touserdata(L, -2);
			int allign = lua_tonumber(L, -1);
			obj->AddObject(obj0, Object::Allign(allign));
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

	/*
		Box child class wrapper
	*/
	int mboxid = LUA.newtable("MenuBox");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			float dX = lua_tonumber(L, -2);
			float dY = lua_tonumber(L, -1);
			void* newobj = lua_newuserdata(L, sizeof(MenuBox));
			new (newobj) MenuBox(dX, dY);
			luaL_getmetatable(L, "MenuBoxMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	//inheritance of Box methods
	LUA.setmetatable("BoxMetaTable");

	LUA.newmetatable("MenuBoxMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			MenuBox* obj = (MenuBox*)lua_touserdata(L, -1);
			obj->~MenuBox();
			return 0;
		});
	LUA.setvalue("__index", mboxid);

	int textid = LUA.newtable("Text");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			std::string text = lua_tostring(L, -2);
			float size = lua_tonumber(L, -1);
			void* newobj = lua_newuserdata(L, sizeof(Text));
			new (newobj) Text(text, LOCAL("default"), size);
			luaL_getmetatable(L, "TextMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	//inheritance of Object methods
	LUA.setmetatable("ObjectMetaTable");

	LUA.newmetatable("TextMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Text* obj = (Text*)lua_touserdata(L, -1);
			obj->~Text();
			return 0;
		});
	LUA.setvalue("__index", mboxid);

	///FUNCTIONS

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

	LUA.pushfunction("DisplayMessage", [](lua_State* L) -> int
		{
			std::string txt = lua_tostring(L, -1);
			DisplayMessage(txt);
			return 1;
		});

	LUA.pushfunction("DisplayError", [](lua_State* L) -> int
		{
			std::string txt = lua_tostring(L, -1);
			DisplayError(txt);
			return 1;
		});
}
