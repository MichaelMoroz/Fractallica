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
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new Object();
			luaL_getmetatable(L, "ObjectMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("SetPosition", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -3);
			float posX = lua_tonumber(L, -2);
			float posY = lua_tonumber(L, -1);
			obj->SetPosition(posX, posY);
			return 1;
		});
	LUA.setfunction("AddObject", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -3);
			Object* obj0 = *(Object**)lua_touserdata(L, -2);
			int allign = lua_tonumber(L, -1);
			obj->AddObject(obj0, Object::Allign(allign));
			return 1;
		});
	LUA.setfunction("SetDefaultFunction", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			call_func c = GetLuaCallbackFunction(L);
			obj->SetDefaultFunction(c);
			return 1;
		});
	LUA.setfunction("SetCallbackFunction", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			call_func c = GetLuaCallbackFunction(L);
			obj->SetCallbackFunction(c);
			return 1;
		});
	LUA.setfunction("SetHoverFunction", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			call_func c = GetLuaCallbackFunction(L);
			obj->SetHoverFunction(c);
			return 1;
		});
	LUA.setfunction("SetText", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			std::string text = lua_tostring(L, -1);
			obj->SetData(&text);//tries to set the string as data,
								//can go really bad if tried to set on something else than a text obj
			return 1;
		});

	LUA.newmetatable("ObjectMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -1);
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
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new Box(dX, dY);
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
			Box* obj = *(Box**)lua_touserdata(L, -1);
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
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new MenuBox(dX, dY);
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
			MenuBox* obj = *(MenuBox**)lua_touserdata(L, -1);
			obj->~MenuBox();
			return 0;
		});
	LUA.setvalue("__index", mboxid);

	int textid = LUA.newtable("Text");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			std::string text = lua_tostring(L, -2);
			float size = lua_tonumber(L, -1);
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new Text(text, LOCAL("default"), size);
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
			Text* obj = *(Text**)lua_touserdata(L, -1);
			obj->~Text();
			return 0;
		});
	LUA.setvalue("__index", mboxid);

	///FUNCTIONS

	///Add global object
	LUA.pushfunction("AddGlobalObject", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -1);
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

void AddObject2LuaStack(LuaVM* LVM, Object* obj)
{
	LVM->newuserdatafrom(obj, "ObjectMetaTable");
}

call_func GetLuaCallbackFunction(lua_State* L)
{
	int function_id = luaL_ref(L, LUA_REGISTRYINDEX);
	return [L, function_id](sf::RenderWindow* window, InputState& state, Object* obj)
	{
		//push function onto stack
		lua_rawgeti(L, LUA_REGISTRYINDEX, function_id); 
		//push object onto stack
		//assuming that Lua only stores the pointer as userdata
		void** dt = (void**)lua_newuserdata(L, sizeof(void*));
		*dt = obj; //set the pointer to point at the data
		luaL_getmetatable(L, "ObjectMetaTable");
		lua_setmetatable(L, -2);
		/* do the call (1 arguments, 0 results) */
		if (lua_pcall(L, 1, 0, 0) != 0)
		{
			//error
		}
	};
}
