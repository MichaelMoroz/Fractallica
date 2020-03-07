function OpenDebugInfo()
	local wind0 = Window.new(interface_size.x - 500, 700, 500, 500, "Debug");
	wind0:SetUnique(true);
	local framename = Text.new("Frame:", 30);
	local frametxt = Text.new("", 30);
	function frameupd(object)
		object:SetText(tostring(frame));
	end
	frametxt:SetDefaultFunction(true, frameupd);
	
	local fpsname = Text.new("FPS:", 30);
	local fpstxt = Text.new("", 30);
	function fpsupd(object)
		object:SetText(tostring(math.floor(GetFPS()+0.5)));
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

console_log = " \n";
console_log_delta = "";
command_str = "";
console_obj_delta = nil;

--global copy of the consolelog object
consolelog = MenuBox.new(796, 600);

function Add2Console(obj)
	console_obj_delta = obj;
end;

function PrintConsole(text)
	Add2Console(Text.new(text,20));
end;

newlinemargin = Box.new(796, 0);
newlinemargin:SetBackgroundColor(Color.Transparent);

function Add2ConsoleLog(object)
	if(console_log_delta ~= "") then
		object:AddObject2MenuBox(Text.new(console_log_delta, 20),Allign.LEFT);
		object:AddObject2MenuBox(newlinemargin,Allign.LEFT);
		consolelog:AddObject2MenuBox(Text.new(console_log_delta, 20),Allign.LEFT);
		consolelog:AddObject2MenuBox(newlinemargin,Allign.LEFT);
		console_log_delta = "";
		object:SetRepeatLimit();
	end;
	if(console_obj_delta ~= nil) then
		object:AddObject2MenuBox(console_obj_delta,Allign.LEFT);
		object:AddObject2MenuBox(newlinemargin,Allign.LEFT);
		consolelog:AddObject2MenuBox(console_obj_delta,Allign.LEFT);
		consolelog:AddObject2MenuBox(newlinemargin,Allign.LEFT);
		console_obj_delta = nil;
		object:SetRepeatLimit();
	end;
end;

consolelog:SetDefaultFunction(true, Add2ConsoleLog);

function OpenConsole()
	local wind0 = Window.new(100, 100, 800, 500, "Console");
	wind0:SetUnique(true);
	
	function execcommand(object)
        clicksound:Play();
		console_log = console_log..">>"..command_str;
        local err = dostring(command_str);
		console_log = console_log.."\n"..err.."\n";
		if(err == "") then
			console_log_delta = ">>"..command_str;
		else
			console_log_delta = ">>"..command_str.."\n"..err;
		end;	
    end;
	
	local command = InputBox.new(700, 35);
    function updatestr(object)
        command_str = object:GetText();
		if(IsButtonPressed(Key.Enter)) then
			execcommand(object);
			object:SetRepeatLimit();
		end;
    end;
    command:SetDefaultFunction(false, updatestr);
    
   
    local runbtn = Button.new("Run", 100, 35, execcommand);
	
	wind0:AddObject(consolelog, Allign.LEFT);
	wind0:AddObject(command, Allign.LEFT);
	wind0:AddObject(runbtn, Allign.RIGHT);
	AddGlobalObject(wind0);
end;

console_title_str = Text.new("Fractallica Alpha "..GetVersion().." - Lua command console", 30);
console_title_str:SetBackgroundColor(Color.Yellow);
Add2Console(console_title_str);