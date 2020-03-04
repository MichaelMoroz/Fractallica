#pragma once

#include<Resources.h>
#include<Settings.h>
#include<config.h>
#include<Localization.h>
#include<Interface.h>
#include<Renderer.h>
#include<LuaVM.h>
#include<ResourcesLua.h>

#define DEBUG_MODE 1

extern sf::Clock screenshot_clock;
extern InputState io_state;

//Constants
extern float target_fps;
extern float smooth_fps;
extern float lag_ms;

void SetPointers(sf::RenderWindow * w, sf::Texture * main, sf::Texture * screensht);

void RunInitialScript();
void RunLoopScript();
void RunRenderScript();

void OpenTestWindow();
void ConfirmExit();
void DisplayError(std::string error_text);
void DisplayMessage(std::string text);
void LockMouse(sf::RenderWindow& window);
void UnlockMouse(sf::RenderWindow& window);
int DirExists(const char *path);

void GameOpLua();
sf::Vector2i getResolution(int i);

void InitializeWindow(bool fullscreen, float FPSlimit);



