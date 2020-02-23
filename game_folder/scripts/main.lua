--[[
  The initial Lua script called by Fractallica
]]--

--Load the table saving library
dofile( "scripts/libs/table.save-1.0.lua" )

OpenTestWindow();

box = Box.new(250,250);

box:SetPosition(300,500);

AddGlobalObject(box);