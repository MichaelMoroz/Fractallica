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

function OpenInputTest()
	local wind = Window.new(400, 400, 300, 400, "Input test");
	local boxW = Box.new(100, 100);
	boxW:AddObject(Text.new("W", 60), Allign.CENTER);
	
	function CW(object)
		if(IsButtonPressed(Key.W)) then
			object:SetBackgroundColor(Color.Red);
		else
			object:SetBackgroundColor(Color.Gray);
		end;
	end
	
	boxW:SetDefaultFunction(true, CW); --set global(true) and always updating function CW
	
	local boxA = Box.new(100, 100);
	boxA:AddObject(Text.new("A", 60), Allign.CENTER);
	function CA(object)
		if(IsButtonPressed(Key.A)) then
			object:SetBackgroundColor(Color.Red);
		else
			object:SetBackgroundColor(Color.Gray);
		end;
	end
	boxA:SetDefaultFunction(true, CA);
	
	local boxS = Box.new(100, 100);
	boxS:AddObject(Text.new("S", 60), Allign.CENTER);
	function CS(object)
		if(IsButtonPressed(Key.S)) then
			object:SetBackgroundColor(Color.Red);
		else
			object:SetBackgroundColor(Color.Gray);
		end;
	end
	boxS:SetDefaultFunction(true, CS);
	
	local boxD = Box.new(100, 100);
	boxD:AddObject(Text.new("D", 60), Allign.CENTER);
	function CD(object)
		if(IsButtonPressed(Key.D)) then
			object:SetBackgroundColor(Color.Red);
		else
			object:SetBackgroundColor(Color.Gray);
		end;
	end
	boxD:SetDefaultFunction(true, CD);
	
	wind:AddObject(boxW, Allign.CENTER);
	wind:AddObject(boxA, Allign.LEFT);
	wind:AddObject(boxD, Allign.RIGHT);
	wind:AddObject(boxS, Allign.CENTER);
	
	AddGlobalObject(wind);
end;

OpenInputTest();

--intialize the shader
dofile( "scripts/compute/noise_init.lua" );