#include "3d.hpp"

void camera3d::update() {
	Camera3D cam = *this;
	UpdateCamera(&cam, CAMERA_FREE);
	position = cam.position;
	target = cam.target;
	up = cam.up;
}

void camera3d::updatepro(vector3 position, vector3 direction, float zoom)
{
	Camera3D cam = *this;
	UpdateCameraPro(&cam, position, direction, zoom);
	position = cam.position;
	target = cam.target;
	up = cam.up;
}