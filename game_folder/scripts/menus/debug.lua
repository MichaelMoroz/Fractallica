
function OpenDebugInfo()
	local wind0 = Window.new(450, 450, 500, 500, "Debug");

	local framename = Text.new("Frame:", 30);
	local frametxt = Text.new("", 30);
	function frameupd(object)
		object:SetText(tostring(frame));
	end
	frametxt:SetDefaultFunction(true, frameupd);
	
	local fpsname = Text.new("FPS:", 30);
	local fpstxt = Text.new("", 30);
	function fpsupd(object)
		object:SetText(tostring(GetFPS()));
	end
	fpstxt:SetDefaultFunction(true, fpsupd);
	
	local margin = Box.new(500, 10);
	margin:SetBackgroundColor(Color.Transparent);
	
	wind0:AddObject(framename, Allign.LEFT);
	wind0:AddObject(frametxt, Allign.RIGHT);
	wind0:AddObject(margin, Allign.CENTER);
	wind0:AddObject(fpsname, Allign.LEFT);
	wind0:AddObject(fpstxt, Allign.RIGHT);
	wind0:AddObject(margin, Allign.CENTER);
	AddGlobalObject(wind0);
end;
