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

Renderer *renderer_ptr;
sf::RenderWindow *window;
sf::Texture *main_txt;
sf::Texture *screenshot_txt;

void SetPointers(sf::RenderWindow *w, Renderer* rd, sf::Texture *main, sf::Texture *screensht)
{
	window = w;
	renderer_ptr = rd;
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

void OpenMainMenu()
{
	RemoveAllObjects();
	game_mode = MAIN_MENU;

	sf::Vector2f wsize = default_size;
	sf::Vector2f vsize = default_view.getSize();
	MenuBox mainmenu(1000, vsize.y*0.95f, false, wsize.x*0.025, wsize.y*0.025f);
	mainmenu.SetBackgroundColor(sf::Color::Transparent);
	//make the menu static
	mainmenu.static_object = true;

	//TITLE
	Text ttl("Fractallica", LOCAL("default"), 120, sf::Color::White);
	ttl.SetBorderColor(sf::Color::Black);
	ttl.SetBorderWidth(4);
	mainmenu.AddObject(&ttl, Object::Allign::LEFT);

	Box margin1(800, 5);
	margin1.SetBackgroundColor(sf::Color::Transparent);
	mainmenu.AddObject(&margin1, Object::Allign::LEFT);

	Text CE("Alpha " + std::string(PROJECT_VER), LOCAL("default"), 60, sf::Color::White);
	CE.SetBorderColor(sf::Color::Black);
	CE.SetBorderWidth(4);
	mainmenu.AddObject(&CE, Object::Allign::LEFT);

	Box margin(800, 80);
	margin.SetBackgroundColor(sf::Color::Transparent);
	mainmenu.AddObject(&margin, Object::Allign::LEFT);

	//Exit
	Box exitbtn(600, 50);
	Text button6(LOCAL["Exit"], LOCAL("default"), 40, sf::Color::White);
	button6.SetBorderColor(sf::Color::Black);
	exitbtn.hoverstate.color_main = sf::Color(200, 40, 0, 255);
	exitbtn.SetCallbackFunction([](sf::RenderWindow * window, InputState & state)
	{
		window->close();
	}, true);
	exitbtn.AddObject(&button6, Object::Allign::CENTER);
	mainmenu.AddObject(&exitbtn, Object::Allign::LEFT);
	

	AddGlobalObject(mainmenu);
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

	get_glob_obj(id).objects[1].get()->objects[0].get()->objects[1].get()->SetCallbackFunction([id](sf::RenderWindow * window, InputState & state)
	{
		window->close();
	});

	get_glob_obj(id).objects[1].get()->objects[0].get()->objects[2].get()->SetCallbackFunction([id](sf::RenderWindow * window, InputState & state)
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
		[](sf::RenderWindow * window, InputState & state)
		{
			
		},
		sf::Color(200, 40, 0, 255), sf::Color(128, 128, 128, 128)), Object::Allign::RIGHT);

	int id = AddGlobalObject(error_window);

	get_glob_obj(id).objects[1].get()->objects[0].get()->objects[1].get()->SetCallbackFunction(
	[id](sf::RenderWindow * window, InputState & state)
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


void TakeScreenshot()
{
	taken_screenshot = true;
	sf::Vector2i rendering_resolution = getResolution(SETTINGS.stg.rendering_resolution);
	sf::Vector2i screenshot_resolution = getResolution(SETTINGS.stg.screenshot_resolution);

	renderer_ptr->ReInitialize(screenshot_resolution.x, screenshot_resolution.y);
	renderer_ptr->SetOutputTexture(*screenshot_txt);

	renderer_ptr->camera.SetMotionBlur(0);
	
	//a few rendering steps to converge the TXAA
	for(int i = 0; i < SETTINGS.stg.screenshot_samples; i++) 	renderer_ptr->Render();
	window -> resetGLStates();
	screenshot_txt->copyToImage().saveToFile((std::string)"screenshots/screenshot" + (std::string)num2str(time(NULL)) + ".jpg");

	renderer_ptr->ReInitialize(rendering_resolution.x, rendering_resolution.y);
	renderer_ptr->SetOutputTexture(*main_txt);
	screenshot_clock.restart();
}


void UpdateUniforms()
{
	renderer_ptr->camera.bloomintensity = SETTINGS.stg.bloom_intensity;
	renderer_ptr->camera.bloomradius = SETTINGS.stg.bloom_radius;
	renderer_ptr->camera.auto_exposure_speed = SETTINGS.stg.auto_exposure_speed;
	renderer_ptr->camera.auto_exposure_target = SETTINGS.stg.auto_exposure_target;
	renderer_ptr->camera.SetMotionBlur(SETTINGS.stg.motion_blur);
	renderer_ptr->camera.SetFOV(SETTINGS.stg.FOV);
	renderer_ptr->camera.cross_eye = SETTINGS.stg.cross_eye;
	renderer_ptr->camera.eye_separation = SETTINGS.stg.eye_separation;
	renderer_ptr->camera.SetBokehRadius(SETTINGS.stg.DOF_max);
}

void InitializeRendering(std::string config)
{
	sf::Vector2i rendering_resolution = getResolution(SETTINGS.stg.rendering_resolution);
	sf::Vector2i screenshot_resolution = getResolution(SETTINGS.stg.screenshot_resolution);

	renderer_ptr->variables["MRRM_scale"] = SETTINGS.stg.MRRM_scale;
	renderer_ptr->variables["shadow_scale"] = SETTINGS.stg.shadow_resolution;
	renderer_ptr->variables["bloom_scale"] = SETTINGS.stg.bloom_resolution;
	renderer_ptr->Initialize(rendering_resolution.x, rendering_resolution.y, renderer_ptr->GetConfigFolder() + "/" + config);
	
	UpdateUniforms();
	renderer_ptr->camera.SetFocus(SETTINGS.stg.DOF_focus);
	renderer_ptr->camera.SetExposure(SETTINGS.stg.exposure);
	
	main_txt->create(rendering_resolution.x, rendering_resolution.y);
	renderer_ptr->SetOutputTexture(*main_txt);
	screenshot_txt->create(screenshot_resolution.x, screenshot_resolution.y);
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

		window->create(screen_size, "Marble Marcher: Community Edition", window_style, settings);
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

	std::vector<std::string> configs = renderer_ptr->GetConfigurationsList();

	InitializeRendering(configs[SETTINGS.stg.shader_config]);
}

void RestoreSettings(void* data)
{
	SETTINGS.RestoreDefaults();
	ApplySettings(data);
}
