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

fractal = {Scale = 1.93, Angle1 = 1.34637, Angle2 = 1.58,
		   ShiftX = -2.31, ShiftY = 1.123, ShiftZ = 1.56};
		   
fractal_rng = {Scale = {0, 2.}, Angle1 = {0, 2.*math.pi}, Angle2 = {0, 2.*math.pi},
		   ShiftX = {-5., 5.}, ShiftY = {-5., 5.}, ShiftZ = {-5., 5.}};

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
OpenDebugInfo();
FractalEditor();
--intialize the shader
dofile( "scripts/compute/simple.lua" );