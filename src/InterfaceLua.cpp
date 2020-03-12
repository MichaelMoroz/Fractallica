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
	LUA.setfunction("SetBorderColor", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			vec4 color = **(vec4**)lua_touserdata(L, -1) * 255.f;
			obj->SetBorderColor(sf::Color((int)color.x, (int)color.y, (int)color.z, (int)color.w));
			return 1;
		});
	LUA.setfunction("SetBackgroundColor", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			vec4 color = **(vec4**)lua_touserdata(L, -1) * 255.f;
			obj->SetBackgroundColor(sf::Color((int)color.x, (int)color.y, (int)color.z, (int)color.w));
			return 1;
		});
	LUA.setfunction("SetBorderWidth", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			float w = lua_tonumber(L, -1);
			obj->SetBorderWidth(w);
			return 1;
		});
	LUA.setfunction("SetSize", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -3);
			float w = lua_tonumber(L, -2);
			float h = lua_tonumber(L, -1);
			obj->SetSize(w,h);
			return 1;
		});
	LUA.setfunction("SetHeigth", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			float h = lua_tonumber(L, -1);
			obj->SetHeigth(h);
			return 1;
		});
	LUA.setfunction("SetWidth", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			float w = lua_tonumber(L, -1);
			obj->SetWidth(w);
			return 1;
		});
	LUA.setfunction("SetMargin", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			float w = lua_tonumber(L, -1);
			obj->SetMargin(w);
			return 1;
		});
	LUA.setfunction("SetScroll", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			float w = lua_tonumber(L, -1);
			obj->SetScroll(w);
			return 1;
		});
	LUA.setfunction("SetBorderColor", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -2);
			vec4 color = **(vec4**)lua_touserdata(L, -1) * 255.f;
			obj->SetBorderColor(sf::Color((int)color.x, (int)color.y, (int)color.z, (int)color.w));
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
	LUA.setfunction("AddObject2MenuBox", [](lua_State* L) -> int
		{
			MenuBox* obj = *(MenuBox**)lua_touserdata(L, -3);
			Object* obj0 = *(Object**)lua_touserdata(L, -2);
			int allign = lua_tonumber(L, -1);
			obj->AddObject(obj0, Object::Allign(allign));
			return 1;
		});
	LUA.setfunction("SetDefaultFunction", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -3);
			bool b = lua_toboolean(L, -2);
			call_func c = GetLuaCallbackFunction(L);
			obj->SetDefaultFunction(c, b);
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
	LUA.setfunction("UpdateSlider", [](lua_State* L) -> int
		{
			MenuBox* obj = *(MenuBox**)lua_touserdata(L, -2);
			obj->UpdateSlider();
			return 1;
		});
	LUA.setfunction("SetStatic", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -1);
			obj->static_object = !obj->static_object;
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
	LUA.setfunction("AddText", [](lua_State* L) -> int
		{
			Text* obj = *(Text**)lua_touserdata(L, -2);
			std::string text = lua_tostring(L, -1);
			obj->AddString(text);
			return 1;
		});

	LUA.setfunction("GetValue", [](lua_State* L) -> int
		{
			Slider* obj = *(Slider**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->GetValue());			
			return 1;
		});
	LUA.setfunction("GetObject", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -1);
			int i = lua_tonumber(L, -1);
			Object* o = *(Object**)lua_newuserdata(L, sizeof(void*));
			o = obj->objects[i].get();
			luaL_getmetatable(L, "ObjectPtr");
			lua_setmetatable(L, -2);
			return 1;
		});

	LUA.setfunction("GetText", [](lua_State* L) -> int
		{
			InputBox* obj = *(InputBox**)lua_touserdata(L, -1);
			lua_pushstring(L, obj->GetText().c_str());
			return 1;
		});
	LUA.setfunction("SetRepeatLimit", [](lua_State* L) -> int
		{
			Object* obj = *(Object**)lua_touserdata(L, -3);
			obj->action_time = action_dt;
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

	//metatable for the object pointer, with the destructor overwritten 
	LUA.newmetatable("ObjectPtr");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			//do nothing
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

	/*
		Button child class wrapper
	*/

	int buttonid = LUA.newtable("Button");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			std::string text = lua_tostring(L, -4);
			float dX = lua_tonumber(L, -3);
			float dY = lua_tonumber(L, -2);
			call_func c = GetLuaCallbackFunction(L);
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new Button(text, dX, dY, c);
			luaL_getmetatable(L, "ButtonMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	//inheritance of Box methods
	LUA.setmetatable("BoxMetaTable");

	LUA.newmetatable("ButtonMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Button* obj = *(Button**)lua_touserdata(L, -1);
			obj->~Button();
			return 0;
		});
	LUA.setvalue("__index", buttonid);

	/*
		InputBox child class wrapper
	*/

	int inboxid = LUA.newtable("InputBox");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			float dX = lua_tonumber(L, -2);
			float dY = lua_tonumber(L, -1);
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new InputBox(dX, dY);
			luaL_getmetatable(L, "InputBoxMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	//inheritance of Box methods
	LUA.setmetatable("BoxMetaTable");

	LUA.newmetatable("InputBoxMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			InputBox* obj = *(InputBox**)lua_touserdata(L, -1);
			obj->~InputBox();
			return 0;
		});
	LUA.setvalue("__index", inboxid);

	/*
		Window child class wrapper
	*/
	//float x, float y, float dx, float dy,
	int windowid = LUA.newtable("Window");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			float X = lua_tonumber(L, -5);
			float Y = lua_tonumber(L, -4);
			float dX = lua_tonumber(L, -3);
			float dY = lua_tonumber(L, -2);
			std::string text = lua_tostring(L, -1);
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new Window(X, Y, dX, dY, default_main_color, LOCAL[text]);
			luaL_getmetatable(L, "WindowMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("AddCloseCallback", [](lua_State* L) -> int
		{
			Window* obj = *(Window**)lua_touserdata(L, -2);
			call_func c = GetLuaCallbackFunction(L);
			obj->AddCloseCallback(c);
			return 1;
		});
	LUA.setfunction("SetUnique", [](lua_State* L) -> int
		{
			Window* obj = *(Window**)lua_touserdata(L, -2);
			bool unq = lua_toboolean(L, -1);
			obj->SetUnique(unq);
			return 1;
		});
	//inheritance of Box methods
	LUA.setmetatable("BoxMetaTable");

	LUA.newmetatable("WindowMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Window* obj = *(Window**)lua_touserdata(L, -1);
			obj->~Window();
			return 0;
		});
	LUA.setvalue("__index", windowid);

	/*
		Slider child class wrapper
	*/
	//float x, float y, float dx, float dy,
	int sliderid = LUA.newtable("Slider");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			float dX = lua_tonumber(L, -6);
			float dY = lua_tonumber(L, -5);
			float val = lua_tonumber(L, -4);
			float dv = lua_tonumber(L, -3);
			float maxv = lua_tonumber(L, -2);
			float minv = lua_tonumber(L, -1);
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new Slider(dX, dY, val, dv, maxv, minv);
			luaL_getmetatable(L, "SliderMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	//inheritance of Box methods
	LUA.setmetatable("BoxMetaTable");

	LUA.newmetatable("SliderMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Slider* obj = *(Slider**)lua_touserdata(L, -1);
			obj->~Slider();
			return 0;
		});
	LUA.setvalue("__index", sliderid);

	/*
		Image child class wrapper
	*/
	//float x, float y, float dx, float dy,
	int imgid = LUA.newtable("ImageBox");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			sf::Texture *X = *(sf::Texture**)lua_touserdata(L, -3);
			float dX = lua_tonumber(L, -2);
			float dY = lua_tonumber(L, -1);
			void** newobj = (void**)lua_newuserdata(L, sizeof(void*));
			*newobj = new Image(*X, dX, dY, sf::Color::White);
			luaL_getmetatable(L, "ImageBoxMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	//inheritance of Box methods
	LUA.setmetatable("BoxMetaTable");

	LUA.newmetatable("ImageBoxMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Image* obj = *(Image**)lua_touserdata(L, -1);
			obj->~Image();
			return 0;
		});
	LUA.setvalue("__index", imgid);

	/*
		Text class wrapper
	*/
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

	LUA.pushfunction("RemoveAllObjects", [](lua_State* L) -> int
		{
			RemoveAllObjects();
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

	LUA.Clear();
}

void AddObject2LuaStack(LuaVM* LVM, Object* obj)
{
	LVM->newuserdatafrom(obj, "ObjectPtr");
}

call_func GetLuaCallbackFunction(lua_State* L)
{
	int function_id = luaL_ref(L, LUA_REGISTRYINDEX);
	return [L, function_id](sf::RenderWindow* window, InputState& state, Object* obj)
	{
		//push function onto stack
		lua_rawgeti(L, LUA_REGISTRYINDEX, function_id); //rawgeti spaghetti
		//push object onto stack
		//assuming that Lua only stores the pointer as userdata
		void** dt = (void**)lua_newuserdata(L, sizeof(void*));
		*dt = obj; //set the pointer to point at the data
		luaL_getmetatable(L, "ObjectPtr");
		lua_setmetatable(L, -2);
		/* do the call (1 arguments, 0 results) */
		if (lua_pcall(L, 1, 0, 0) != 0)
		{
			//error
		}
	};
}
