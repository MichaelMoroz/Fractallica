#include "Gamemodes.h"


//Global variables
sf::Vector2i mouse_pos, mouse_prev_pos;
InputState io_state;

bool fullscreen_current = false;
bool all_keys[sf::Keyboard::KeyCount] = { 0 };
bool mouse_clicked = false;
bool show_cheats = false;
bool taken_screenshot = false;
sf::Clock screenshot_clock;
//Constants

float target_fps = 60.0f;

GameMode game_mode = MAIN_MENU;

sf::RenderWindow *window;
sf::Texture *main_txt;
sf::Texture *screenshot_txt;

void SetPointers(sf::RenderWindow *w,  sf::Texture *main, sf::Texture *screensht)
{
	window = w;	
	main_txt = main;
	screenshot_txt = screensht;
}

/*
	The scripts that runs 1 time at the launch
*/
void RunInitialScript()
{
	LUA.DoFile(main_lua);
	auto e = LUA.check_error_msg();
	if (e.first != LUA_OK)
	{
		DisplayError(e.second);
	}
}

void RunLoopScript()
{
	LUA.DoFile(loop_lua);
}

void RunRenderScript()
{
	LUA.DoFile(render_lua);
}

void OpenTestWindow()
{
	Window test(200, 200, 500, 500, sf::Color(0, 0, 0, 128), LOCAL["Window"], LOCAL("default"));
	Text button(LOCAL["Button"], LOCAL("default"), 30, sf::Color::White);
	Box sbox(0, 0, 420, 200, sf::Color(128, 128, 128, 240));
	Box sbox2(0, 0, 240, 40, sf::Color(0, 64, 128, 240));
	Box sbox3(0, 0, 30, 30, sf::Color(0, 64, 128, 240));

	sbox2.hoverstate.color_main = sf::Color(230, 40, 20, 200);
	sbox2.AddObject(&button, Box::CENTER);
	button.hoverstate.font_size = 40;
	test.Add(&sbox, Box::CENTER);
	test.Add(&sbox2, Box::CENTER);
	test.Add(&sbox, Box::CENTER);
	test.Add(&sbox2, Box::CENTER);
	test.Add(&sbox, Box::CENTER);
	test.Add(&sbox2, Box::CENTER);
	
	AddGlobalObject(test);
}

void ConfirmExit()
{
	sf::Vector2f wsize = default_size;
	Window confirm(wsize.x*0.4f, wsize.y*0.4f, 500, 215, sf::Color(0, 0, 0, 128), LOCAL["You_sure"], LOCAL("default"));
	Text button1(LOCAL["Yes"], LOCAL("default"), 30, sf::Color::White);
	Text button2(LOCAL["No"], LOCAL("default"), 30, sf::Color::White);
	Text text(LOCAL["You_sure"], LOCAL("default"), 30, sf::Color::White);

	Box but1(0, 0, 240, 40, sf::Color(0, 64, 128, 240));
	Box but2(0, 0, 240, 40, sf::Color(0, 64, 128, 240));

	but1.hoverstate.color_main = sf::Color(230, 40, 20, 200);
	but2.hoverstate.color_main = sf::Color(40, 230, 20, 200);
	but1.AddObject(&button1, Box::CENTER);
	but2.AddObject(&button2, Box::CENTER);

	confirm.Add(&text, Box::CENTER);
	confirm.Add(&but1, Box::RIGHT);
	confirm.Add(&but2, Box::RIGHT);

	int id = AddGlobalObject(confirm);

	get_glob_obj(id).objects[1].get()->objects[0].get()->objects[1].get()->SetCallbackFunction([id](sf::RenderWindow * window, InputState & state, Object* this_obj)
	{
		window->close();
	});

	get_glob_obj(id).objects[1].get()->objects[0].get()->objects[2].get()->SetCallbackFunction([id](sf::RenderWindow * window, InputState & state, Object* this_obj)
	{
		Add2DeleteQueue(id);
	});
}


void DisplayError(std::string error_text)
{
	sf::Vector2f wsize = default_size;
	Window error_window(wsize.x*0.5f - 640, wsize.y*0.5f, 1280, 215, sf::Color(100, 0, 0, 128), LOCAL["Lua compilation error"], LOCAL("default"));
	
	error_window.Add(new Text(error_text, LOCAL("default"), 15, sf::Color::Red), Object::Allign::LEFT);

	error_window.Add(new Button(LOCAL["Ok"], 240, 40,
		[](sf::RenderWindow * window, InputState & state, Object* this_obj)
		{
			
		},
		sf::Color(200, 40, 0, 255), sf::Color(128, 128, 128, 128)), Object::Allign::RIGHT);

	int id = AddGlobalObject(error_window);

	get_glob_obj(id).objects[1].get()->objects[0].get()->objects[1].get()->SetCallbackFunction(
	[id](sf::RenderWindow * window, InputState & state, Object* this_obj)
	{
		Add2DeleteQueue(id);
	});
}

void DisplayMessage(std::string text)
{
	sf::Vector2f wsize = default_size;
	Window error_window(wsize.x * 0.5f - 640, wsize.y * 0.5f, 1280, 215, sf::Color(100, 100, 100, 128), LOCAL["Information"], LOCAL("default"));

	error_window.Add(new Text(text, LOCAL("default"), 15, sf::Color::White), Object::Allign::LEFT);

	error_window.Add(new Button(LOCAL["Ok"], 240, 40,
		[](sf::RenderWindow* window, InputState& state, Object* this_obj)
		{

		},
		sf::Color(200, 40, 0, 255), sf::Color(128, 128, 128, 128)), Object::Allign::RIGHT);

	int id = AddGlobalObject(error_window);

	get_glob_obj(id).objects[1].get()->objects[0].get()->objects[1].get()->SetCallbackFunction(
		[id](sf::RenderWindow* window, InputState& state, Object* this_obj)
		{
			Add2DeleteQueue(id);
		});
}

void LockMouse(sf::RenderWindow& window) {
	window.setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(window.getSize().x*0.5, window.getSize().y*0.5), window);
	mouse_prev_pos = sf::Vector2i(window.getSize().x * 0.5, window.getSize().y * 0.5);
	mouse_pos = sf::Vector2i(window.getSize().x * 0.5, window.getSize().y * 0.5);
}

void UnlockMouse(sf::RenderWindow& window) {
	window.setMouseCursorVisible(true);
}

int DirExists(const char *path) {
	return (int)fs::exists(fs::path(path));
}

sf::Vector2i getResolution(int i)
{
	switch (i)
	{
	case 0:
		return sf::Vector2i(320, 240);
	case 1:
		return sf::Vector2i(480, 320);
	case 2:
		return sf::Vector2i(640, 480);
	case 3:
		return sf::Vector2i(800, 480);
	case 4:
		return sf::Vector2i(960, 540);
	case 5:
		return sf::Vector2i(1136, 640);
	case 6:
		return sf::Vector2i(1280, 720);
	case 7:
		return sf::Vector2i(1600, 900);
	case 8:
		return sf::Vector2i(1920, 1080);
	case 9:
		return sf::Vector2i(2048, 1152);
	case 10:
		return sf::Vector2i(2560, 1440);
	case 11:
		return sf::Vector2i(3840, 2160);
	case 12:
		return sf::Vector2i(7680, 4320);
	case 13:
		return sf::Vector2i(10240, 4320);
	case 14:
		return sf::Vector2i(240, 140);
	}
}


void InitializeWindow(bool fullscreen, float FPSlimit)
{
	if (!window->isOpen() || fullscreen != fullscreen_current)
	{
		fullscreen_current = fullscreen;

		sf::VideoMode screen_size;
		sf::Uint32 window_style;
		if (fullscreen) {
			screen_size = sf::VideoMode::getDesktopMode();
			window_style = sf::Style::Fullscreen;
		}
		else {
			screen_size = sf::VideoMode::getDesktopMode();
			window_style = sf::Style::Default;
		}

		//GL settings
		sf::ContextSettings settings;
		settings.majorVersion = 4;
		settings.minorVersion = 3;

		window->create(screen_size, "Fractallica", window_style, settings);
		window->setVerticalSyncEnabled(SETTINGS.stg.VSYNC);
		window->setKeyRepeatEnabled(false);

		INIT();

		if (!fullscreen)
		{
			sf::VideoMode fs_size = sf::VideoMode::getDesktopMode();
			window->setSize(sf::Vector2u(fs_size.width, fs_size.height - 100.f));
			window->setPosition(sf::Vector2i(0, 0));
		}
	}
	window->setFramerateLimit(FPSlimit);
}

void ApplySettings(void *data)
{
	//if window is not yet created or when the fullscreen setting is changed
	if (!window->isOpen() || SETTINGS.stg.fullscreen != fullscreen_current)
	{
		fullscreen_current = SETTINGS.stg.fullscreen;

		sf::VideoMode screen_size;
		sf::Uint32 window_style;
		bool fullscreen = SETTINGS.stg.fullscreen;
		if (fullscreen) {
			screen_size = sf::VideoMode::getDesktopMode();
			window_style = sf::Style::Fullscreen;
		}
		else {
			screen_size = sf::VideoMode::getDesktopMode();
			window_style = sf::Style::Default;
		}

		//GL settings
		sf::ContextSettings settings;
		settings.majorVersion = 4;
		settings.minorVersion = 3;

		window->create(screen_size, "Fractallica", window_style, settings);
		window->setVerticalSyncEnabled(SETTINGS.stg.VSYNC);
		window->setKeyRepeatEnabled(false);

		INIT();

		if (!fullscreen)
		{
			sf::VideoMode fs_size = sf::VideoMode::getDesktopMode();
			window->setSize(sf::Vector2u(fs_size.width, fs_size.height - 100.f));
			window->setPosition(sf::Vector2i(0, 0));
		}

		SETTINGS.first_start = false;
	}

	window->setFramerateLimit(SETTINGS.stg.fps_limit);
	std::vector<std::string> langs = LOCAL.GetLanguages();
	LOCAL.SetLanguage(langs[SETTINGS.stg.language]);
}

//global Lua functions
void GameOpLua()
{
	LUA.pushfunction("CloseFractallica", [](lua_State* L) -> int
		{
			window->close();
			return 1;
		});
	
	LUA.pushfunction("InitializeWindow", [](lua_State* L) -> int
		{
			bool fullscreen = lua_toboolean(L, -2);
			float FPSlim = lua_tonumber(L, -1);
			InitializeWindow(fullscreen, FPSlim);
			return 1;
		});

	LUA.pushfunction("InitializeRenderTextures", [](lua_State* L) -> int
		{
			float W = lua_tonumber(L, -4);
			float H = lua_tonumber(L, -3);
			float Ws = lua_tonumber(L, -2);
			float Hs = lua_tonumber(L, -1);
			main_txt->create(W, H);
			screenshot_txt->create(Ws, Hs);
			return 1;
		});

	LUA.pushfunction("GetLanguages", [](lua_State* L) -> int
		{
			std::vector<std::string> langs = LOCAL.GetLanguages();
			int langnum = langs.size(); /* set this dynamically */
			lua_createtable(L, langnum, 0);
			for (int i = 0; i < langnum; i++) {
				lua_pushstring(L, langs[i].c_str());
				lua_rawseti(L, -2, i + 1); /* In lua indices start at 1 */
			}
			return 1;
		});

	LUA.pushfunction("SetLanguage", [](lua_State* L) -> int
		{
			std::string lang = lua_tostring(L, -1);
			LOCAL.SetLanguage(lang);
			return 1;
		});

	LUA.pushfunction("GetWindowSize", [](lua_State* L) -> int
		{
			PushVector(vec2(window->getSize().x, window->getSize().y));
			return 1;
		});

	LUA.pushfunction("GetVersion", [](lua_State* L) -> int
		{
			lua_pushstring(L, PROJECT_VER);
			return 1;
		});
}

void RestoreSettings(void* data)
{
	SETTINGS.RestoreDefaults();
	ApplySettings(data);
}
