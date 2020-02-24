--[[
  The initial Lua script called by Fractallica
]]--

--Load the table saving library
dofile( "scripts/libs/table.save-1.0.lua" )
dofile( "scripts/libs/definitions.lua" )

menu = MenuBox.new(250,600);

menu:SetPosition(300,500);

menu:AddObject(Text.new("KEK", 50), Allign.LEFT);

AddGlobalObject(menu);

camera = Camera.new();

camera:setPosition(10, 15, 30);

shadertest = ComputeShader.new("scripts/compute/noise/noise.glsl");

shadertest:setCameraObj("Camera1", camera);