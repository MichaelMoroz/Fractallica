--[[
  The initial Lua script called by Fractallica
]]--

--Load the table saving library
dofile( "scripts/libs/table.save-1.0.lua" )
dofile( "scripts/libs/definitions.lua" )
dofile( "scripts/menus/main_menu.lua" );

camera = Camera.new();

camera:setPosition(10, 15, 30);

frame = 0;

OpenMainMenu();

--intialize the shader
dofile( "scripts/compute/noise_init.lua" );