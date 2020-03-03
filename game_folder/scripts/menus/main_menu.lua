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
	local version = Text.new("Alpha 0.0.2", 40);
	--version.SetBorderColor(Color.Black);
	--version.SetBorderWidth(4);
	
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