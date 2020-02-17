#include <Camera.h>

void Camera::SetPosition(vec3 pos)
{
	position = pos;
}

void Camera::RotateLR(float a)
{
	//rotate around UP direction
	quat rotation = angleAxis(degrees(a), GetDirY());
	dirx = rotation*dirx;
	dirz = rotation*dirz;
}

void Camera::RotateUD(float a)
{
	//rotate around sideways direction
	quat rotation = angleAxis(degrees(a), GetDirZ());
	dirx = rotation*dirx;
	diry = rotation*diry;
}

void Camera::RotateRoll(float a)
{
	//rotate around look direction
	quat rotation = angleAxis(degrees(a), GetDirX());
	diry = rotation*diry;
	dirz = rotation*dirz;
}

void Camera::SetRotation(float a, float b, float c)
{
	vec3 Euler(a, b, c);
	quat rotation(Euler);
	dirx = rotation*quat(0, 1, 0, 0);
	diry = rotation*quat(0, 0, 1, 0);
	dirz = rotation*quat(0, 0, 0, 1);
}

//k = 0 - absolutely sharp movements, 1 - infinitely smooth movements, best ~0.1
void Camera::SetSmoothness(float k)
{
	smooth = k;
}

void Camera::Shift(vec3 dx)
{
	position += dx;
}

void Camera::Move(vec3 dv)
{
	velocity += dv.x*GetDirX() + dv.y*GetDirY() + dv.z*GetDirZ();
}

void Camera::RotateX(float a)
{
	alpha += a;
}

void Camera::RotateY(float a)
{
	beta += a;
}

void Camera::Roll(float a)
{
	gamma += a;
}

void Camera::Update(float dt)
{
	//interpolate
	dt = (dt*smooth + 1 - smooth);

	Shift(velocity*dt);
	RotateLR(alpha*dt);
	RotateUD(beta*dt);
	RotateRoll(gamma*dt);

	//exponential decay of our velocities, if smooth = 1 - they won't decay at all
	velocity -= (1 - smooth)*velocity*dt;
	alpha -= (1 - smooth)*alpha*dt;
	beta -= (1 - smooth)*beta*dt;
	gamma -= (1 - smooth)*gamma*dt;
}

void Camera::SetDirY(vec3 dir)
{
	diry.x = dir.x;
	diry.y = dir.y;
	diry.z = dir.z;
}

void Camera::SetDirZ(vec3 dir)
{
	dirz.x = dir.x;
	dirz.y = dir.y;
	dirz.z = dir.z;
}

void Camera::UpdateExposure(float illumination)
{
	exposure = exp(clamp(log(exposure + auto_exposure_speed*(auto_exposure_target - illumination)*exposure), -auto_exposure_range * 0.5f, auto_exposure_range * 0.5f));
}

vec3 Camera::GetPosition()
{
	if (cur_mode == ThirdPerson)
	{
		return position - radius*GetDirX();
	}

	return position;
}

vec3 Camera::GetDirX()
{
	return normalize(vec3(dirx.x, dirx.y, dirx.z));
}

vec3 Camera::GetDirY()
{
	return normalize(vec3(diry.x, diry.y, diry.z));
}

vec3 Camera::GetDirZ() 
{
	return normalize(vec3(dirz.x, dirz.y, dirz.z));
}

vec4 Camera::GetCameraProperties()
{
	return vec4(FOV, exposure, focus, bokeh);
}

vec4 Camera::GetCameraProperties2()
{
	return vec4(size, mblur, speckle, 0);
}

void Camera::Fpp()
{
	iFrame++;
}

gl_camera Camera::GetGLdata()
{
	gl_camera cam;
	cam.position = GetPosition();
	cam.dirx = GetDirX();
	cam.diry = GetDirY();
	cam.dirz = GetDirZ();
	
	cam.aspect_ratio = aspect_ratio;
	cam.FOV = tan(FOV*3.14159 / 360);
	cam.focus = focus;
	cam.bokeh = bokeh;
	cam.exposure = exposure;
	cam.mblur = mblur;
	cam.speckle = speckle;
	cam.size = size;
	cam.bloomintensity = bloomintensity;
	cam.bloomradius = bloomradius;

	//data for the renderer
	cam.resolution = resolution; //not a property of the camera, but of the renderer
	cam.cross_eye = cross_eye;
	cam.eye_separation = eye_separation;
	cam.iFrame = iFrame;
	return cam;
}

void Camera::SetMode(CameraMode mode)
{
	cur_mode = mode;
}

void Camera::SetRadius(float r)
{
	radius = r;
}

void Camera::SetFOV(float fov)
{
	FOV = fov;
}

void Camera::SetAspectRatio(float asr)
{
	aspect_ratio = asr;
}

void Camera::SetBokehRadius(float b)
{
	bokeh = b;
}

void Camera::SetMotionBlur(float mb)
{
	mblur = mb;
}

void Camera::SetExposure(float e)
{
	exposure = e;
}

void Camera::SetFocus(float f)
{
	focus = f;
}

void Camera::SetSpeckleRadius(float s)
{
	speckle = s;
}

void Camera::SetCameraSize(float s)
{
	size = s;
}

void Camera::SetResolution(vec2 res)
{
	resolution = res;
}

void Camera::LookAt(vec3 pos)
{
	//todo
}

void Camera::SetDirX(vec3 dir)
{
	dirx.x = dir.x;
	dirx.y = dir.y;
	dirx.z = dir.z;
}
