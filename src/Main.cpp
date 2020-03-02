#include <Gamemodes.h>
#include "Res.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <LuaVM.h>
#include <InterfaceLua.h>
#include <ShadersLua.h>
#include <ResourcesLua.h>

#ifdef _WIN32
#include <Windows.h>
#define ERROR_MSG(x) MessageBox(nullptr, TEXT(x), TEXT("ERROR"), MB_OK);
#else
#define ERROR_MSG(x) std::cerr << x << std::endl;
#endif
 

#if defined(_WIN32)
int WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpCmdLine, int nCmdShow) {
#else
int main(int argc, char *argv[]) {
#endif
	bool first_start = SETTINGS.Load(settings_bin);

	//all of the fonts
	Fonts fonts;
	LOCAL.LoadLocalsFromFolder(local_folder, &fonts);
	
	//all declarations
	sf::RenderWindow window;
  
	Renderer rend(main_config);
	sf::Texture main_txt, screenshot_txt;
	
	sf::Clock clock;
	float smooth_fps = target_fps;
	float lag_ms = 0.0f;
	mouse_pos = sf::Vector2i(0, 0);
	mouse_prev_pos = sf::Vector2i(0, 0);
  
	SetPointers(&window, &rend, &main_txt, &screenshot_txt);

	ApplySettings(nullptr);

	window.requestFocus();
	UpdateAspectRatio(window.getSize().x, window.getSize().y);
	//set window icon
	//sf::Image icon;
	//icon.loadFromFile(icon_png); 
	//window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	rend.LoadExternalTextures(textures_folder);
  
	sf::View default_window_view = window.getDefaultView();


	io_state.window_size = sf::Vector2f(window.getSize().x, window.getSize().y);
	float prev_s = 0;
	
	//init LUA
	WrapInterface(&LUA);
	WrapShaders(&LUA);
	WrapResources(&LUA);
	GameOpLua();
	AddGlobalTexture("main_texture", &main_txt);
	AddGlobalTexture("screenshot_texture", &screenshot_txt);

	RunInitialScript();

	#define n_touch 5
	sf::Vector2i touch_xy[n_touch];
	sf::Vector2i touch_pxy[n_touch];
	bool touched[n_touch] = { false };

	sf::CircleShape touch_circle[n_touch], joystick;

	for (int i = 0; i < n_touch; i++)
	{
		touch_circle[i].setRadius(0);
		touch_circle[i].setFillColor(sf::Color(128, 128, 128, 200));
	}
	joystick.setRadius(0);
	joystick.setFillColor(sf::Color(128, 128, 128, 128));
	int joystick_finger = -1;
	int view_finger = -1;

	//Main loop
	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::White);
		float mouse_wheel = 0.0f;
		mouse_prev_pos = mouse_pos;
		io_state.mouse_prev = sf::Vector2f(mouse_prev_pos.x, mouse_prev_pos.y);
		io_state.wheel = mouse_wheel;
		io_state.mouse_press[2] = false;
		io_state.mouse_press[0] = false;
		bool TOUCH_MODE = SETTINGS.stg.touch_mode;

		for (int i = 0; i < n_touch; i++)
		{
			//previous touch state
			touch_pxy[i] = touch_xy[i];
		}

		for (int i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			io_state.key_press[i] = false;
		}

		for (int i = 0; i < sf::Joystick::AxisCount; i++)
		{
			io_state.axis_moved[i] = false;
		}

		for (int i = 0; i < sf::Joystick::ButtonCount; i++)
		{
			io_state.button_pressed[i] = false;
		}

		while (window.pollEvent(event)) 
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			const sf::Keyboard::Key keycode = event.key.code;
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
			
				default_window_view = sf::View(visibleArea);
				window.setView(default_window_view);
				io_state.window_size = sf::Vector2f(window.getSize().x, window.getSize().y);
				UpdateAspectRatio(window.getSize().x, window.getSize().y);
				rend.camera.SetAspectRatio((float)window.getSize().x / (float)window.getSize().y);
				break;
			case sf::Event::TouchBegan:
				touched[event.touch.finger] = true;
				touch_pxy[event.touch.finger] = sf::Vector2i(event.touch.x, event.touch.y);
				if (event.touch.finger < n_touch)
				{
					touch_circle[event.touch.finger].setRadius(60);
				}
				//the joystick half of the screen
				if (event.touch.x < window.getSize().x / 2)
				{
					if (joystick_finger < 0)
					{
						joystick_finger = event.touch.finger;
						joystick.setRadius(120);
						joystick.setPosition(event.touch.x - joystick.getRadius(), event.touch.y - joystick.getRadius());
					}
				}
				else //the view half of the screen
				{
					if (view_finger < 0)
					{
						view_finger = event.touch.finger;
					}
				}
				break;
			case sf::Event::TouchEnded:
				touched[event.touch.finger] = false;
				if (event.touch.finger < n_touch)
				{
					touch_circle[event.touch.finger].setRadius(0);
				}
				if (joystick_finger == event.touch.finger)
				{
					joystick_finger = -1;
					joystick.setRadius(0);
				}
				if (view_finger == event.touch.finger)
				{
					view_finger = -1;
				}
				break;
			case sf::Event::JoystickButtonPressed:
				io_state.buttons[event.joystickButton.button] = true;
				io_state.button_pressed[event.joystickButton.button] = true;
				break;
			case sf::Event::JoystickButtonReleased:
				io_state.buttons[event.joystickButton.button] = false;
				break;
			case sf::Event::JoystickMoved:
				io_state.axis_value[event.joystickMove.axis] =
					(abs(event.joystickMove.position) < SETTINGS.stg.gamepad_deadzone) ? 0.f : event.joystickMove.position;
				io_state.axis_moved[event.joystickMove.axis] = true;
				break;
			case sf::Event::KeyPressed:
				all_keys[keycode] = true;
				io_state.isKeyPressed = true;
				io_state.keys[keycode] = true;
				io_state.key_press[keycode] = true;
				if (keycode == sf::Keyboard::Escape)
				{
					if (game_mode == MAIN_MENU)
					{
						if (NumberOfObjects() < 2)
							ConfirmExit();
					}
				}
				break;
			case sf::Event::KeyReleased:
				if (event.key.code < 0 || event.key.code >= sf::Keyboard::KeyCount) { continue; }
				all_keys[keycode] = false;
				io_state.keys[keycode] = false;
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mouse_pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
					mouse_clicked = true;
					io_state.mouse[0] = true;
					io_state.mouse_press[0] = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Right && !TOUCH_MODE)
				{
					io_state.mouse[2] = true;
					io_state.mouse_press[2] = true;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					io_state.mouse[0] = false;
					mouse_pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
					mouse_clicked = false;
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					io_state.mouse[2] = false;
				}
				break;
			case sf::Event::MouseMoved:
				mouse_pos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
				io_state.mouse_pos = sf::Vector2f(mouse_pos.x, mouse_pos.y);
				break;
			case sf::Event::MouseWheelScrolled:
				mouse_wheel += event.mouseWheelScroll.delta;
				io_state.wheel = mouse_wheel;
				break;
			}
		}

		RunLoopScript();

		//touch circles
		int touches = 0;
		for (int i = 0; i < n_touch; i++)
		{
			if (touched[i])
			{
				touches++;
				//touch state
				touch_xy[i] = sf::Touch::getPosition(i, window);
				touch_circle[i].setPosition(touch_xy[i].x - touch_circle[i].getRadius(), touch_xy[i].y - touch_circle[i].getRadius());
			}
		}
	
		bool skip_frame = false;
		if ((lag_ms >= 1000.0f / target_fps) && SETTINGS.stg.speed_regulation) {
			//If there is too much lag, just do another frame of physics and skip the draw
			lag_ms -= 1000.0f / target_fps;
			skip_frame = true;
		}
		else 
		{
			//Update the shader values
			if (game_mode != FIRST_START)
			{
				if (!(taken_screenshot && SETTINGS.stg.screenshot_preview))
				{
					RunRenderScript();
					window.resetGLStates();
					//Draw render texture to main window
					sf::Sprite sprite(main_txt);
					sprite.setScale(float(window.getSize().x) / float(main_txt.getSize().x),
						float(window.getSize().y) / float(main_txt.getSize().y));
					window.draw(sprite);
				}
				else
				{
					//Draw screenshot preview
					sf::Sprite sprite(screenshot_txt);
					sf::Vector2u ssize = screenshot_txt.getSize();
					float scale = min(float(window.getSize().x) / float(ssize.x),
						float(window.getSize().y) / float(ssize.y));
					vec2 pos = vec2(window.getSize().x - ssize.x*scale, window.getSize().y - ssize.y*scale)*0.5f;
					sprite.setScale(scale, scale);
					sprite.setPosition(pos.x, pos.y);
					window.draw(sprite);

					const float s = screenshot_clock.getElapsedTime().asSeconds();
					if (s > SETTINGS.stg.preview_time)
					{
						taken_screenshot = false;
					}
				}
			}
		}

		//new interface render stuff
		io_state.dt = prev_s;
		io_state.time += io_state.dt;
		UpdateAllObjects(&window, io_state);
		io_state.isKeyPressed = false;
		window.setView(default_window_view);
		UpdateUniforms();
		
		if (!skip_frame) {
			if (TOUCH_MODE)
			{
				for (int i = 0; i < n_touch; i++)
				{
					window.draw(touch_circle[i]);
				}
				if (game_mode == PLAYING || game_mode == CREDITS || game_mode == MIDPOINT || game_mode == LEVEL_EDITOR)
				{
					window.draw(joystick);
		    	}
			}

			window.display();

			//If V-Sync is running higher than desired fps, slow down!
			const float s = clock.restart().asSeconds();
			prev_s = s;
			if (s > 0.0f) {
				smooth_fps = smooth_fps * 0.9f + std::min(1.0f / s, target_fps)*0.1f;
			}
			const float time_diff_ms = 1000.0f * (1.0f / target_fps - s);
			if (time_diff_ms > 0) {
				sf::sleep(sf::seconds(time_diff_ms / 1000.0f));
				lag_ms = std::max(lag_ms - time_diff_ms, 0.0f);
			}
			else if (time_diff_ms < 0) {
				lag_ms += std::max(-time_diff_ms, 0.0f);
			}
		}
	}

	//Remove all interface objects
	RemoveAllObjects();
	return 0;
}
