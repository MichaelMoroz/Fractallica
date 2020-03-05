function OpenMainMenu()
	CURRENT_MODE = GAME_MODES.MENU;
	
	RemoveAllObjects();
	--all objects here are local, thus are destroyed after this function ends
	local mainmenu = MenuBox.new(1000,800);
	mainmenu:SetStatic(); --unchanging render order 
	mainmenu:SetPosition(0.025*interface_size.x,0.025*interface_size.y);

	local margin = Box.new(1000*0.9, 5);
	margin:SetBackgroundColor(Color.Transparent);
	local title = Text.new("Fractallica", 120);
	title:SetBorderColor(Color.Black);
	title:SetBorderWidth(4);
	local version = Text.new("Alpha " .. GetVersion(), 40);
	
	function exitcallback(object)
		CloseFractallica();
	end;
	local exitbtn = Button.new("Exit", 600, 50, exitcallback);
	
	function freecam(object)
		Free_Camera_Mode();
	end;
	local fcbtn = Button.new("Free camera mode", 600, 50, freecam);
	
	mainmenu:AddObject(title, Allign.LEFT);
	mainmenu:AddObject(margin, Allign.CENTER);
	mainmenu:AddObject(version, Allign.LEFT);
	mainmenu:AddObject(margin, Allign.CENTER);
	mainmenu:AddObject(fcbtn, Allign.LEFT);
	mainmenu:AddObject(exitbtn, Allign.LEFT);
	
	--add a copy of the mainmenu object to the global render/update list
	AddGlobalObject(mainmenu);
end;


function FractalEditor()
	local wind = Window.new(400, 400, 600, 400, "Fractal parameters");
	
	local margin = Box.new(600, 15);
	margin:SetBackgroundColor(Color.Transparent);
	
	local fname0 = Text.new("Just a text input", 30);
	local inbox = InputBox.new(300, 35);
	wind:AddObject(fname0, Allign.LEFT);
	wind:AddObject(inbox, Allign.RIGHT);
	wind:AddObject(margin, Allign.CENTER);
	for k, v in pairs(fractal) do
		local fname = Text.new(k, 30);
		local val = Text.new("", 30);
		local slid = Slider.new(280, 30, fractal[k], fractal_rng[k][1], fractal_rng[k][2], 0.);
		function updateval0(object)
			fractal[k] = object:GetValue();
		end
		function updateval1(object)
			object:SetText(tostringp(fractal[k], 0.001));
		end
		val:SetDefaultFunction(true, updateval1);
		slid:SetDefaultFunction(true, updateval0);
		wind:AddObject(fname, Allign.LEFT);
		wind:AddObject(slid, Allign.RIGHT);
		wind:AddObject(val, Allign.RIGHT);
		wind:AddObject(margin, Allign.CENTER);
	end
	
	AddGlobalObject(wind);
end;
