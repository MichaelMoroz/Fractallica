--[[
  The initial Lua script called by Fractallica
]]--

--Load the table saving library
dofile( "scripts/libs/table.save-1.0.lua" )
dofile( "scripts/libs/definitions.lua" )
dofile( "scripts/menus/main_menu.lua" );
dofile( "scripts/menus/input_test.lua" );
render = {width = 320, height = 240};

--initial stuff
--fullscreen and FPS limit
InitializeWindow(false, 60); 
--main and screenshot resolution
InitializeRenderTextures(render.width, render.height, render.width, render.height);
--used localization file
SetLanguage("English");

frame = 0;

camera = Camera.new();

camera:setPosition(-100, 0, 0);
camera:SetExposure(0.5);

OpenMainMenu();

OpenInputTest();

--intialize the shader
dofile( "scripts/compute/simple.lua" );