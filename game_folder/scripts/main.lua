--[[
  The initial Lua script called by Fractallica
]]--

--Load the table saving library
dofile( "scripts/libs/table.save-1.0.lua" )
dofile( "scripts/libs/definitions.lua" )

box = Box.new(250,600);

box:SetPosition(300,500);

iterator = 0;

function weird_callback(object)
	iterator = iterator + 1;
	object:SetText(tostring(iterator));
end;

weird_text = Text.new("inirgwff", 50);
weird_text:SetCallbackFunction(weird_callback);
box:AddObject(weird_text, Allign.LEFT);

AddGlobalObject(box);

camera = Camera.new();

camera:setPosition(10, 15, 30);

--[[shadertest = ComputeShader.new("scripts/compute/noise/noise.glsl");

shadertest:setCameraObj("Camera1", camera);

shadertest:setInt("iFrame", 0);

Bind(0, main_texture, GL_READ_WRITE);

shadertest:Run(1280,720);--]]