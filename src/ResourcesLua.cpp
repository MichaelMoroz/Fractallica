#include "ResourcesLua.h"

void WrapResources(LuaVM * LVM)
{
	int imgid = LUA.newtable("Texture");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			void* newobj = lua_newuserdata(L, sizeof(sf::Texture));
			new (newobj) sf::Texture();
			luaL_getmetatable(L, "TextureMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});
	LUA.setfunction("create", [](lua_State* L) -> int
		{
			sf::Texture* obj = (sf::Texture*)lua_touserdata(L, -3);
			int posX = lua_tonumber(L, -2);
			int posY = lua_tonumber(L, -1);
			obj->create(posX, posY);
			return 1;
		});
	LUA.setfunction("loadFromFile", [](lua_State* L) -> int
		{
			sf::Texture* obj = (sf::Texture*)lua_touserdata(L, -2);
			std::string fname = lua_tostring(L, -1);
			obj->loadFromFile(fname);
			return 1;
		});

	LUA.newmetatable("TextureMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			sf::Texture* obj = (sf::Texture*)lua_touserdata(L, -1);
			obj->~Texture();
			return 0;
		});

	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", imgid);


	//HDR texture
	int imgid = LUA.newtable("Texture32f");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			int dX = lua_tonumber(L, -2);
			int dY = lua_tonumber(L, -1);
			void* obj = lua_newuserdata(L, sizeof(GLuint));
			GLuint *texture = static_cast<GLuint*>(obj);
			glGenTextures(1, texture);
			glBindTexture(GL_TEXTURE_2D, *texture);
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
	LUA.setvalue("__index", imgid);

}
