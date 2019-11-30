#include "Camera.h"

Camera::Camera(int pixelwidth, int pixelheight)
{
	this->pixelwidth = pixelwidth;
	this->pixelheight = pixelheight;
	fieldofview = 60;
	nearclipplane = 0.3f;
	farclipplane = 1000.0f;
}

Camera::~Camera()
{
}

void Camera::prepare_render()
{
	Matrix view, proj;
	Quaternion rot;
	Quaternion::euler(&rot, euler);
	Matrix::view(&view, position, rot);
	Matrix::perspective(&proj, fieldofview * DEG_TO_RAD, aspect(), nearclipplane, farclipplane);

	set_current_viewmatrix(view);
	set_current_projmatrix(proj);
}

Matrix Camera::get_viewmatrix()
{
	return _view;
}

Matrix Camera::get_projmatrix()
{
	return _proj;
}

float Camera::aspect()
{
	return float(pixelwidth) / pixelheight;
}

void Camera::set_current_viewmatrix(Matrix matrix)
{
	_view = matrix;
}

void Camera::set_current_projmatrix(Matrix matrix)
{
	_proj = matrix;
}

Matrix Camera::_view = Matrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
Matrix Camera::_proj = Matrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);