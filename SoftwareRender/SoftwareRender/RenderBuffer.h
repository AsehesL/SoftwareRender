#pragma once
#include "Color.h"

class RenderBuffer
{
public:
	RenderBuffer();
	~RenderBuffer();
	void set_pixel(int, int, Color);
	void set_depth(int, int, float);
};

