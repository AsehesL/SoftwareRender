#pragma once
#include "Color.h"

extern "C" {
#include "SDL.h"
}

class RenderBuffer
{
public:
	RenderBuffer();
	~RenderBuffer();
	void set_pixel(int, int, Color);
	void set_depth(int, int, float);
	float get_depth(int, int);

protected:
	int _width, _height;
};

