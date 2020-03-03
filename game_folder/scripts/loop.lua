--[[ 
	This script is executed each engine frame
	Mainly should be used for physics and gameplay
]]--

frame = frame + 1;
camera:setPosition(0., 0., -7.);
camera:RotateX(0.0001*math.sin(frame/60));
camera:Update(1/60);
wind_size = GetWindowSize();
camera:SetAspectRatio(wind_size:x()/wind_size:y());