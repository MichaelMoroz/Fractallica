function Free_Camera_Mode()
	CURRENT_MODE = GAME_MODES.FREE_CAMERA;
	RemoveAllObjects();
	cam_velocity = 0.1;
	mouse_sensitivity = 0.0003;
	local title = Text.new("Free camera mode", 60);
	AddGlobalObject(title);
end;

function Free_Camera_Update()
	dx = 0; dy = 0; dz = 0;
	if(IsButtonPressed(Key.W)) then
		dy = cam_velocity;
	end;
	if(IsButtonPressed(Key.S)) then
		dy = -cam_velocity;
	end;
	if(IsButtonPressed(Key.D)) then
		dx = cam_velocity;
	end;
	if(IsButtonPressed(Key.A)) then
		dx = -cam_velocity;
	end;
	
	camera:Move(dx, dy, dz);
	if(IsMousePressed(0)) then
		local dmouse = GetMouseVel();
		camera:RotateX(mouse_sensitivity*dmouse:x());
		camera:RotateY(mouse_sensitivity*dmouse:y());
	end;
	
	if(IsButtonPressed(Key.Q)) then
		camera:Roll(mouse_sensitivity);
	end;
	if(IsButtonPressed(Key.E)) then
		camera:Roll(-mouse_sensitivity);
	end;
	
	if(IsButtonPressed(Key.Escape)) then
		OpenMainMenu();
	end;
	
	cam_velocity = cam_velocity*(1+0.1*GetMouseWheel());
	
end;