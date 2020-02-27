--[[ 
	This script is executed each time the engine renders a frame
	it can be executed less frequently than the loop script
]]--

shader:setCameraObj("Camera1", camera);

shader:setInt("iFrame", frame);

Bind(0, main_texture, GL_READ_WRITE);

shader:Run(1280/8,720/8);