--Shader initialization 

MRRM1 = ComputeShader.new("scripts/compute/multires_marching/MRRM1.glsl"); 
MRRM2 = ComputeShader.new("scripts/compute/multires_marching/MRRM2.glsl");
simple_render = ComputeShader.new("scripts/compute/main/simple_shading.glsl"); 

MRRM_scale = 5;
group_size = 8;

-- G-BUFFER
-- pixel positions
depth0 = Texture32f.new(render.width/MRRM_scale,render.height/MRRM_scale);
depth1 = Texture32f.new(render.width/MRRM_scale,render.height/MRRM_scale);
various = Texture32f.new(render.width/MRRM_scale,render.height/MRRM_scale);

depth = Texture32f.new(render.width,render.height);
depth_prev = Texture32f.new(render.width,render.height);
normals = Texture32f.new(render.width,render.height);
HDR = Texture32f.new(render.width,render.height);
HDR_prev = Texture32f.new(render.width,render.height);

function ApplyDefaultParams(shader)
	shader:setFloat("iFracScale",1.93);
	shader:setFloat("iFracAng1",1.93);
	shader:setFloat("iFracAng2",1.93);
	shader:setVec3("iFracShift", -2.31, 1.123, 1.56);
	shader:setVec3("iFracCol", 0.42, 0.38, 0.19);
	shader:setVec3("iMarblePos", -1.71412, 1.84836, -1.70884);
	shader:setVec3("iFlagPos", 0.0, 2.13651, 1.74782);
	shader:setFloat("iMarbleRad",0.02);
	shader:setFloat("iFlagScale",0.02);
	shader:setInt("FRACTAL_ITER",16);
	shader:setInt("MARBLE_MODE",0);
	shader:setFloat("time",0);
	shader:setFloat("PBR_METALLIC",0.5);
	shader:setFloat("PBR_ROUGHNESS",0.5);
	shader:setVec3("LIGHT_DIRECTION", 0.0, 2.13651, 1.74782);
	shader:setBool("SHADOWS_ENABLED",1);
	shader:setBool("FRACTAL_GLOW",0);
	shader:setBool("FLAG_GLOW",0);
	shader:setFloat("gamma_material",0.6);
	shader:setFloat("gamma_sky",0.6);
	shader:setFloat("gamma_camera",2.2);
end;

ApplyDefaultParams(MRRM1);
ApplyDefaultParams(MRRM2);
ApplyDefaultParams(simple_render);

function DoRender()
	MRRM1:setCameraObj("Camera", camera);
	MRRM1:setInt("iFrame", frame);
	MRRM2:setCameraObj("Camera", camera);
	MRRM2:setInt("iFrame", frame);
	simple_render:setCameraObj("Camera", camera);
	simple_render:setInt("iFrame", frame);

	Bind32f(0, depth0, GL_READ_WRITE);
	Bind32f(1, depth1, GL_READ_WRITE);
	Bind32f(2, various, GL_READ_WRITE);
	Bind32f(3, depth, GL_READ_WRITE);
	Bind32f(4, HDR, GL_READ_WRITE);
	MRRM1:Run(render.width/group_size,render.width/group_size);
	
	Bind32f(0, depth0, GL_READ_WRITE);
	Bind32f(1, depth1, GL_READ_WRITE);
	Bind32f(2, various, GL_READ_WRITE);
	Bind32f(3, depth, GL_READ_WRITE);
	Bind32f(4, depth_prev, GL_READ_WRITE);
	Bind32f(5, normals, GL_READ_WRITE);
	MRRM2:Run(render.width/group_size,render.width/group_size);
	
	Bind(0, main_texture, GL_READ_WRITE); --final texture
	Bind32f(1, depth, GL_READ_WRITE);
	Bind32f(2, depth_prev, GL_READ_WRITE);
	Bind32f(3, normals, GL_READ_WRITE);
	Bind32f(4, HDR, GL_READ_WRITE);
	Bind32f(5, HDR_prev, GL_READ_WRITE);
	simple_render:Run(render.width/group_size,render.width/group_size);
end;