--[[
  The initial Lua script called by Fractallica
]]--

--Load the table saving library
dofile( "scripts/libs/table.save-1.0.lua" );
dofile( "scripts/libs/definitions.lua" );

render = {width = 960, height = 480};

--initial stuff
--fullscreen and FPS limit
InitializeWindow(false, 60); 
--main and screenshot resolution
InitializeRenderTextures(render.width, render.height, render.width, render.height);
--used localization file
SetLanguage("English");

frame = 0;
camera = Camera.new();
camera:setPosition(-10, 0, 0);
camera:SetExposure(0.5);
camera:SetResolution(render.width, render.height);

GAME_MODES = {MENU = 0, FREE_CAMERA = 1};
CURRENT_MODE = 0;

--Free camera mode stuff
dofile( "scripts/gamemodes/free_cam.lua" );

--Menus
dofile( "scripts/menus/main_menu.lua" );
dofile( "scripts/menus/input_test.lua" );
dofile( "scripts/menus/debug.lua" );

OpenMainMenu();
OpenInputTest();
OpenDebugInfo();
--intialize the shader
dofile( "scripts/compute/simple.lua" );