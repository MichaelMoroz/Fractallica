#include "ShadersLua.h"

void WrapShaders(LuaVM* LVM)
{
	int shaderid = LUA.newtable("ComputeShader");
	LUA.setfunction("new", [](lua_State* L) -> int
		{
			std::string path = std::string(lua_tostring(L, -1));
			ComputeShader** newobj = (ComputeShader**)lua_newuserdata(L, sizeof(void*));
			*newobj = new ComputeShader(path);
			luaL_getmetatable(L, "ShaderMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});

	LUA.setfunction("Run", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -3);
			float nx = ceil(lua_tonumber(L, -2));
			float ny = ceil(lua_tonumber(L, -1));
			obj->Run(vec2(nx, ny));
			return 1;
		});

	LUA.setfunction("setInt", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -3);
			std::string name = std::string(lua_tostring(L, -2));
			int nx = lua_tonumber(L, -1);
			obj->setUniform(name, nx);
			return 1;
		});

	LUA.setfunction("setFloat", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -3);
			std::string name = std::string(lua_tostring(L, -2));
			float nx = lua_tonumber(L, -1);
			obj->setUniform(name, nx);
			return 1;
		});

	LUA.setfunction("setVec2", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -4);
			std::string name = std::string(lua_tostring(L, -3));
			float nx = lua_tonumber(L, -2);
			float ny = lua_tonumber(L, -1);
			obj->setUniform(name, nx, ny);
			return 1;
		});

	LUA.setfunction("setVec3", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -5);
			std::string name = std::string(lua_tostring(L, -4));
			float nx = lua_tonumber(L, -3);
			float ny = lua_tonumber(L, -2);
			float nz = lua_tonumber(L, -1);
			obj->setUniform(name, nx, ny, nz);
			return 1;
		});

	LUA.setfunction("setBool", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -3);
			std::string name = std::string(lua_tostring(L, -2));
			bool nx = lua_toboolean(L, -1);
			obj->setUniform(name, nx);
			return 1;
		});

	LUA.setfunction("setCameraObj", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -3);
			std::string name = std::string(lua_tostring(L, -2));
			Camera* cam = (Camera*)lua_touserdata(L, -1);
			obj->setCameraObj(name, cam->GetGLdata());
			return 1;
		});

	LUA.setfunction("setTexture32f", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -3);
			std::string name = std::string(lua_tostring(L, -2));
			GLuint X = *(GLuint*)lua_touserdata(L, -1);
			obj->setUniform(name, X);
			return 1;
		});

	LUA.setfunction("setTexture", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -3);
			std::string name = std::string(lua_tostring(L, -2));
			sf::Texture* X = *(sf::Texture**)lua_touserdata(L, -1);
			obj->setUniform(name, X->getNativeHandle());
			return 1;
		});

	LUA.newmetatable("ShaderMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			ComputeShader* obj = *(ComputeShader**)lua_touserdata(L, -1);
			obj->Delete();
			return 0;
		});

	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", shaderid);

	int camid = LUA.newtable("Camera");

	LUA.setfunction("new", [](lua_State* L) -> int
		{
			void* newobj = lua_newuserdata(L, sizeof(Camera));
			new (newobj) Camera();
			luaL_getmetatable(L, "CameraMetaTable");
			lua_setmetatable(L, -2);
			return 1;
		});

	LUA.setfunction("setPosition", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -4);
			float nx = lua_tonumber(L, -3);
			float ny = lua_tonumber(L, -2);
			float nz = lua_tonumber(L, -1);
			obj->SetPosition(vec3(nx, ny, nz));
			return 1;
		});

	LUA.setfunction("setRotation", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -4);
			float nx = lua_tonumber(L, -3);
			float ny = lua_tonumber(L, -2);
			float nz = lua_tonumber(L, -1);
			obj->SetRotation(nx, ny, nz);
			return 1;
		});

	LUA.setfunction("setResolution", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -3);
			float nx = lua_tonumber(L, -2);
			float ny = lua_tonumber(L, -1);
			obj->SetResolution(vec2(nx, ny));
			return 1;
		});

	LUA.setfunction("Move", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -4);
			float dx = lua_tonumber(L, -3);
			float dy = lua_tonumber(L, -1);
			float dz = lua_tonumber(L, -2);
			obj->Move(vec3(dx, dy, dz));
			return 1;
		});

	LUA.setfunction("RotateX", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -2);
			float dx = lua_tonumber(L, -1);
			obj->RotateX(dx);
			return 1;
		});

	LUA.setfunction("RotateY", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -2);
			float dx = lua_tonumber(L, -1);
			obj->RotateY(dx);
			return 1;
		});

	LUA.setfunction("Roll", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -2);
			float dx = lua_tonumber(L, -1);
			obj->Roll(dx);
			return 1;
		});

	LUA.setfunction("SetExposure", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -2);
			float exposure = lua_tonumber(L, -1);
			obj->SetExposure(exposure);
			return 1;
		});

	LUA.setfunction("Update", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -2);
			float dt = lua_tonumber(L, -1);
			obj->Update(dt);
			return 1;
		});
	LUA.setfunction("SetResolution", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -3);
			float x = lua_tonumber(L, -2);
			float y = lua_tonumber(L, -1);
			obj->SetResolution(vec2(x,y));
			return 1;
		});
	LUA.setfunction("SetAspectRatio", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -2);
			float ar = lua_tonumber(L, -1);
			obj->SetAspectRatio(ar);
			return 1;
		});


	LUA.newmetatable("CameraMetaTable");
	///object destructor
	LUA.setfunction("__gc", [](lua_State* L) -> int
		{
			Camera* obj = (Camera*)lua_touserdata(L, -1);
			obj->~Camera();
			return 0;
		});

	///the thing that links the metatable to the Object table
	LUA.setvalue("__index", camid);


	//Bind images to the compute shader
	LUA.pushfunction("Bind", [](lua_State* L) -> int
		{
			int id = lua_tonumber(L, -3);
			sf::Texture* X = *(sf::Texture**)lua_touserdata(L, -2);
			int RW = lua_tonumber(L, -1); //Read or write
			glBindImageTexture(id, X->getNativeHandle(), 0, GL_FALSE, 0, RW, GL_RGBA8);
			return 1;
		});

	LUA.pushfunction("Bind32f", [](lua_State* L) -> int
		{
			int id = lua_tonumber(L, -3);
			GLint texid = *(GLuint*)lua_touserdata(L, -2);
			int RW = lua_tonumber(L, -1);
			glBindImageTexture(id, texid, 0, GL_FALSE, 0, RW, GL_RGBA32F);
			return 1;
		});

	LUA.Clear();
}
