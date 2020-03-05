--[[ 
	This script is executed each engine frame
	Mainly should be used for physics and gameplay
]]--

if(CURRENT_MODE == GAME_MODES.MENU) then
	camera:setPosition(0., 0., -7.);
	camera:RotateX(0.000*math.sin(frame/60));
else
	Free_Camera_Update();
end;

frame = frame + 1;
camera:Update(0.0001);
wind_size = GetWindowSize();
camera:SetAspectRatio(wind_size:x()/wind_size:y());