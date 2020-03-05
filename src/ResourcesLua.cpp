#include "ResourcesLua.h"

void WrapResources(LuaVM * LVM)
{
	int imgid = LUA.newtable("Texture");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			sf::Texture** newobj = static_cast<sf::Texture**>(lua_newuserdata(L, sizeof(sf::Texture*)));
			*newobj = new sf::Texture();
			luaL_getmetatable(L, "TextureMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("create", [](lua_State* L) -> int
		{
			sf::Texture* obj = *(sf::Texture**)lua_touserdata(L, -3);
			int posX = lua_tonumber(L, -2);
			int posY = lua_tonumber(L, -1);
			obj->create(posX, posY);
			return 1;
		});
	LUA.setfunction("loadFromFile", [](lua_State* L) -> int
		{
			sf::Texture* obj = *(sf::Texture**)lua_touserdata(L, -2);
			std::string fname = lua_tostring(L, -1);
			obj->loadFromFile(fname);
			return 1;
		});
	LUA.setfunction("saveToFile", [](lua_State* L) -> int
		{
			sf::Texture* obj = *(sf::Texture**)lua_touserdata(L, -2);
			std::string fname = lua_tostring(L, -1);
			obj->copyToImage().saveToFile(fname);
			return 1;
		});

	LUA.newmetatable("TextureMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			sf::Texture* obj = *(sf::Texture**)lua_touserdata(L, -1);
			obj->~Texture();
			return 0;
		});

	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", imgid);

	LUA.newmetatable("TexturePtr");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			//nothing
			return 0;
		});

	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", imgid);


	//HDR texture
	int img32id = LUA.newtable("Texture32f");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			int dX = ceil(lua_tonumber(L, -2));
			int dY = ceil(lua_tonumber(L, -1));
			GLuint* obj = (GLuint*)lua_newuserdata(L, sizeof(GLuint));
			new (obj) GLuint();
			glGenTextures(1, obj);
			glBindTexture(GL_TEXTURE_2D, *obj);
			//HDR texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, dX, dY, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			luaL_getmetatable(L, "Texture32fMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});


	LUA.newmetatable("Texture32fMetaTable");

	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			GLuint* obj = (GLuint*)lua_touserdata(L, -1);
			glDeleteTextures(1, obj);
			return 0;
		});
	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", img32id);


	LUA.pushfunction("TextureObject", [](lua_State* L) -> int
		{
			sf::Texture* obj = (sf::Texture*)lua_touserdata(L, -3);
			int posX = lua_tonumber(L, -2);
			int posY = lua_tonumber(L, -1);
			obj->create(posX, posY);
			return 1;
		});

	/*
	bool isKeyPressed;
	bool keys[sf::Keyboard::KeyCount] = { false };
	bool key_press[sf::Keyboard::KeyCount] = { false };
	bool mouse[3] = { false };
	bool mouse_press[3] = { false };
	float wheel = 0.f;
	sf::Vector2f mouse_pos = sf::Vector2f(0,0);
	sf::Vector2f mouse_prev = sf::Vector2f(0, 0);
	sf::Vector2f mouse_speed = sf::Vector2f(0, 0);
	sf::Vector2f window_size = sf::Vector2f(0, 0);
	float time = 0, dt = 0;
	bool axis_moved[sf::Joystick::AxisCount] = { false };
	float axis_value[sf::Joystick::AxisCount] = { 0.f };
	bool  buttons[sf::Joystick::ButtonCount] = { false };
	bool  button_pressed[sf::Joystick::ButtonCount] = { false };
	*/

	//User input stuff
	LUA.pushfunction("IsButtonPressed", [](lua_State* L) -> int
		{
			int keynum = lua_tonumber(L, -1);	
			bool pressed = io_state.keys[keynum];
			lua_pushboolean(L, pressed);
			return 1;
		});
	LUA.pushfunction("IsMousePressed", [](lua_State* L) -> int
		{
			int keynum = lua_tonumber(L, -1);
			bool pressed = io_state.mouse[keynum];
			lua_pushboolean(L, pressed);
			return 1;
		});
	LUA.pushfunction("GetMousePos", [](lua_State* L) -> int
		{
			PushVector(vec2(io_state.mouse_pos.x, io_state.mouse_pos.y));
			return 1;
		});
	LUA.pushfunction("GetMouseVel", [](lua_State* L) -> int
		{
			PushVector(vec2(io_state.mouse_speed.x, io_state.mouse_speed.y));
			return 1;
		});
	LUA.pushfunction("GetMouseWheel", [](lua_State* L) -> int
		{
			lua_pushnumber(L, io_state.wheel);
			return 1;
		});
	LUA.pushfunction("GetWindowSize", [](lua_State* L) -> int
		{
			PushVector(vec2(io_state.window_size.x, io_state.window_size.y));
			return 1;
		});


	//glsl vector2 wrappers
	int vec2id = LUA.newtable("vec2");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			float x = lua_tonumber(L, -2);
			float y = lua_tonumber(L, -1);
			vec2** newobj = static_cast<vec2**>(lua_newuserdata(L, sizeof(void*)));
			*newobj = new vec2(x,y);
			luaL_getmetatable(L, "vec2");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("x", [](lua_State* L) -> int
		{
			vec2* obj = *(vec2**)lua_touserdata(L, -1);		
			lua_pushnumber(L, obj->x);
			return 1;
		});
	LUA.setfunction("y", [](lua_State* L) -> int
		{
			vec2* obj = *(vec2**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->y);
			return 1;
		});

	LUA.newmetatable("vec2");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			vec2* obj = *(vec2**)lua_touserdata(L, -1);
			obj->~vec2();
			return 0;
		});
	LUA.setfunction("__add", [](lua_State* L) -> int
		{
			vec2* obj1 = *(vec2**)lua_touserdata(L, -2);
			vec2* obj2 = *(vec2**)lua_touserdata(L, -1);
			PushVector(*obj1 + *obj2);
			return 0;
		});
	LUA.setfunction("__sub", [](lua_State* L) -> int
		{
			vec2* obj1 = *(vec2**)lua_touserdata(L, -2);
			vec2* obj2 = *(vec2**)lua_touserdata(L, -1);
			PushVector(*obj1 - *obj2);
			return 0;
		});
	LUA.setfunction("__mul", [](lua_State* L) -> int
		{
			vec2* obj1 = *(vec2**)lua_touserdata(L, -2);
			vec2* obj2 = *(vec2**)lua_touserdata(L, -1);
			PushVector(*obj1 * *obj2);
			return 0;
		});
	LUA.setfunction("__div", [](lua_State* L) -> int
		{
			vec2* obj1 = *(vec2**)lua_touserdata(L, -2);
			vec2* obj2 = *(vec2**)lua_touserdata(L, -1);
			PushVector(*obj1 / *obj2);
			return 0;
		});
	LUA.setfunction("__unm", [](lua_State* L) -> int
		{
			vec2* obj = *(vec2**)lua_touserdata(L, -1);
			PushVector(-*obj);
			return 0;
		});
	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", vec2id);

	//glsl vector3 wrappers
	int vec3id = LUA.newtable("vec3");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			float x = lua_tonumber(L, -3);
			float y = lua_tonumber(L, -2);
			float z = lua_tonumber(L, -1);
			vec3** newobj = static_cast<vec3**>(lua_newuserdata(L, sizeof(void*)));
			*newobj = new vec3(x, y, z);
			luaL_getmetatable(L, "vec3");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("x", [](lua_State* L) -> int
		{
			vec3* obj = *(vec3**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->x);
			return 1;
		});
	LUA.setfunction("y", [](lua_State* L) -> int
		{
			vec3* obj = *(vec3**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->y);
			return 1;
		});
	LUA.setfunction("z", [](lua_State* L) -> int
		{
			vec3* obj = *(vec3**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->z);
			return 1;
		});

	LUA.newmetatable("vec3");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			vec3* obj = *(vec3**)lua_touserdata(L, -1);
			obj->~vec3();
			return 0;
		});
	LUA.setfunction("__add", [](lua_State* L) -> int
		{
			vec3* obj1 = *(vec3**)lua_touserdata(L, -2);
			vec3* obj2 = *(vec3**)lua_touserdata(L, -1);
			PushVector(*obj1 + *obj2);
			return 0;
		});
	LUA.setfunction("__sub", [](lua_State* L) -> int
		{
			vec3* obj1 = *(vec3**)lua_touserdata(L, -2);
			vec3* obj2 = *(vec3**)lua_touserdata(L, -1);
			PushVector(*obj1 - *obj2);
			return 0;
		});
	LUA.setfunction("__mul", [](lua_State* L) -> int
		{
			vec3* obj1 = *(vec3**)lua_touserdata(L, -2);
			vec3* obj2 = *(vec3**)lua_touserdata(L, -1);
			PushVector(*obj1 * *obj2);
			return 0;
		});
	LUA.setfunction("__div", [](lua_State* L) -> int
		{
			vec3* obj1 = *(vec3**)lua_touserdata(L, -2);
			vec3* obj2 = *(vec3**)lua_touserdata(L, -1);
			PushVector(*obj1 / *obj2);
			return 0;
		});
	LUA.setfunction("__unm", [](lua_State* L) -> int
		{
			vec3* obj = *(vec3**)lua_touserdata(L, -1);
			PushVector(-*obj);
			return 0;
		});
	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", vec3id);

	//glsl vector4 wrappers
	int vec4id = LUA.newtable("vec4");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			float x = lua_tonumber(L, -4);
			float y = lua_tonumber(L, -3);
			float z = lua_tonumber(L, -2);
			float w = lua_tonumber(L, -1);
			vec4** newobj = static_cast<vec4**>(lua_newuserdata(L, sizeof(void*)));
			*newobj = new vec4(x, y, z, w);
			luaL_getmetatable(L, "vec4");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("x", [](lua_State* L) -> int
		{
			vec4* obj = *(vec4**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->x);
			return 1;
		});
	LUA.setfunction("y", [](lua_State* L) -> int
		{
			vec4* obj = *(vec4**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->y);
			return 1;
		});
	LUA.setfunction("z", [](lua_State* L) -> int
		{
			vec4* obj = *(vec4**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->z);
			return 1;
		});
	LUA.setfunction("w", [](lua_State* L) -> int
		{
			vec4* obj = *(vec4**)lua_touserdata(L, -1);
			lua_pushnumber(L, obj->w);
			return 1;
		});

	LUA.newmetatable("vec4");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			vec4* obj = *(vec4**)lua_touserdata(L, -1);
			obj->~vec4();
			return 0;
		});
	LUA.setfunction("__add", [](lua_State* L) -> int
		{
			vec4* obj1 = *(vec4**)lua_touserdata(L, -2);
			vec4* obj2 = *(vec4**)lua_touserdata(L, -1);
			PushVector(*obj1 + *obj2);
			return 0;
		});
	LUA.setfunction("__sub", [](lua_State* L) -> int
		{
			vec4* obj1 = *(vec4**)lua_touserdata(L, -2);
			vec4* obj2 = *(vec4**)lua_touserdata(L, -1);
			PushVector(*obj1 - *obj2);
			return 0;
		});
	LUA.setfunction("__mul", [](lua_State* L) -> int
		{
			vec4* obj1 = *(vec4**)lua_touserdata(L, -2);
			vec4* obj2 = *(vec4**)lua_touserdata(L, -1);
			PushVector(*obj1 * *obj2);
			return 0;
		});
	LUA.setfunction("__div", [](lua_State* L) -> int
		{
			vec4* obj1 = *(vec4**)lua_touserdata(L, -2);
			vec4* obj2 = *(vec4**)lua_touserdata(L, -1);
			PushVector(*obj1 / *obj2);
			return 0;
		});
	LUA.setfunction("__unm", [](lua_State* L) -> int
		{
			vec4* obj = *(vec4**)lua_touserdata(L, -1);
			PushVector(-*obj);
			return 0;
		});
	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", vec4id);

	LUA.Clear();

	int soundid = LUA.newtable("Sound");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			std::string fname = lua_tostring(L, -1);
			Sound** newobj = static_cast<Sound**>(lua_newuserdata(L, sizeof(void*)));
			*newobj = new Sound(fname);
			luaL_getmetatable(L, "SoundMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("Play", [](lua_State* L) -> int
		{
			Sound* obj = *(Sound**)lua_touserdata(L, -1);
			obj->Play();
			return 1;
		});
	LUA.setfunction("SetVolume", [](lua_State* L) -> int
		{
			Sound* obj = *(Sound**)lua_touserdata(L, -2);
			float x = lua_tonumber(L, -1);
			obj->SetVolume(x);
			return 1;
		});
	LUA.setfunction("SetAttenuation", [](lua_State* L) -> int
		{
			Sound* obj = *(Sound**)lua_touserdata(L, -2);
			float x = lua_tonumber(L, -1);
			obj->SetAttenuation(x);
			return 1;
		});
	LUA.setfunction("SetPosition", [](lua_State* L) -> int
		{
			Sound* obj = *(Sound**)lua_touserdata(L, -2);
			float x = lua_tonumber(L, -1);
			float y = lua_tonumber(L, -2);
			float z = lua_tonumber(L, -3);
			obj->SetPosition(x,y,z);
			return 1;
		});

	LUA.newmetatable("SoundMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Sound* obj = *(Sound**)lua_touserdata(L, -1);
			obj->~Sound();
			return 0;
		});

	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", soundid);
}

void AddGlobalTexture(std::string name, sf::Texture* txt)
{
	LUA.newuserdatafrom(name, txt, "TexturePtr");
}

void PushVector(vec2 a)
{
	vec2* nvec = new vec2(a);
	LUA.newuserdatafrom(nvec, "vec2");
}

void PushVector(vec3 a)
{
	vec3* nvec = new vec3(a);
	LUA.newuserdatafrom(nvec, "vec3");
}

void PushVector(vec4 a)
{
	vec4* nvec = new vec4(a);
	LUA.newuserdatafrom(nvec, "vec4");
}

Sound::Sound(std::string fname)
{
	buff.loadFromFile(fname);
	sound.setBuffer(buff);
}

void Sound::Play()
{
	sound.play();
}

void Sound::SetVolume(float v)
{
	sound.setVolume(v);
}

void Sound::SetPosition(float x, float y, float z)
{
	sound.setPosition(sf::Vector3f(x,y,z));
}

void Sound::SetAttenuation(float a)
{
	sound.setAttenuation(a);
}
