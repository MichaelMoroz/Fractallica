#pragma once
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

#include <new>
#include <LuaVM.h>
#include <Shaders.h>
#include <Interface.h>
#include <Gamemodes.h>

void WrapResources(LuaVM* LVM);
void AddGlobalTexture(std::string name, sf::Texture* txt);
void PushVector(vec2 a);
void PushVector(vec3 a);
void PushVector(vec4 a);

class Sound
{
public:
	Sound(std::string fname);
	void Play();
	void SetVolume(float v);
	void SetPosition(float x, float y, float z);
	void SetAttenuation(float a);
	
	sf::Sound sound;
	sf::SoundBuffer buff;
};