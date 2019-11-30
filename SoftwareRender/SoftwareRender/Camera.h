#pragma once
#include "Math.h"

class Camera
{
public:
	Camera(int pixelwidth, int pixelheight);
	~Camera();
	void prepare_render();
	static Matrix get_viewmatrix();
	static Matrix get_projmatrix();
	float aspect();

private:
	static void set_current_viewmatrix(Matrix matrix);
	static void set_current_projmatrix(Matrix matrix);

public:
	Vector3 position;
	Vector3 euler;
	float fieldofview;
	float nearclipplane;
	float farclipplane;
	int pixelwidth, pixelheight;

private:
	static Matrix _view;
	static Matrix _proj;
};

