#pragma once
#include <string>

#if !defined(__gl_h_) && !defined(__GL_H__) && !defined(_GL_H) && !defined(__X_GL_H)
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <regex>
#include <Camera.h>
#include <filesystem>
#include <map>
#include <algorithm>
#include <sstream>
#include <Res.h>

namespace fs = std::filesystem;

#ifdef _WIN32
#include <Windows.h>
#define ERROR_MSG(x) MessageBox(nullptr, TEXT(x), TEXT("ERROR"), MB_OK);
#else
#include<iostream>
#define ERROR_MSG(x) std::cerr << x << std::endl;
#endif

bool INIT();

class ComputeShader
{
public:
	GLuint ProgramID;

	ComputeShader();
	ComputeShader(const std::string file_path);

	void LoadShader(const std::string file_path);

	void Run(vec2 global);

	void setUniform(std::string name, float X, float Y);
	void setUniform(std::string name, float X, float Y, float Z);
	void setUniform(std::string name, float X);
	void setUniform(std::string name, int X);
	void setUniform(std::string name, glm::mat3 X, bool transpose);
	void setUniform(std::string name, glm::vec3 X);
	void setUniform(std::string name, glm::vec2 X);
	void setUniform(int i, GLuint tid);
	void setCameraObj(std::string name, gl_camera cam);
	void setCamera(gl_camera cam);

	GLuint getNativeHandle();

	std::string PreprocessIncludes(const fs::path & filename, int level = 0);

	void SaveErrors(const fs::path & filename, std::string code, std::string errors);

	std::string LoadFileText(fs::path path);

	void Delete();

private:
	gl_camera prev_camera;
};
