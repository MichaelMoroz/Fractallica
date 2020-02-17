#pragma once

#include<Resources.h>
#include<Settings.h>
#include<config.h>
#include<Localization.h>
#include<Interface.h>
#include<Renderer.h>

#define DEBUG_MODE 1

enum GameMode {
	FIRST_START,
	MAIN_MENU,
	PLAYING,
	PAUSED,
	SCREEN_SAVER,
	CONTROLS,
	LEVELS,
	LEVEL_EDITOR,
	CREDITS,
	MIDPOINT,
	ABOUT,
	MENU
};


//Global variables
extern sf::Vector2i mouse_pos, mouse_prev_pos;
extern bool all_keys[sf::Keyboard::KeyCount];
extern bool mouse_clicked;
extern bool show_cheats;
extern bool taken_screenshot;
extern sf::Clock screenshot_clock;
extern InputState io_state;

//Constants
extern float target_fps;

extern GameMode game_mode;

void OpenMainMenu();
void OpenTestWindow();
void ConfirmExit();
void DisplayError(std::string error_text);
void LockMouse(sf::RenderWindow& window);
void UnlockMouse(sf::RenderWindow& window);
void PauseGame(sf::RenderWindow& window);
int DirExists(const char *path);


void SetPointers(sf::RenderWindow * w, Renderer * rd, sf::Texture * main, sf::Texture * screensht);
sf::Vector2i getResolution(int i);

void TakeScreenshot();
void UpdateUniforms();
void SetCameraFocus(float f);
void ApplySettings(void * data);





